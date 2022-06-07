#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "meshField.h"
#include "camera.h"
#include "model.h"
#include "Obstacle.h"

void Obstacle::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\saikoro.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Obstacle::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Obstacle::Update()
{
	m_Position.y = 0.5f;

	// メッシュフィールド高さ取得
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);

	m_Position.y = meshField->GetHeight(m_Position) + 0.5f;
}

void Obstacle::Draw()
{

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);

	if (!camera->CheckView(m_Position))
		return;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}