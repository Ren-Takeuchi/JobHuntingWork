#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "meshField.h"
#include "camera.h"
#include "Model.h"
#include "player.h"
#include "enemy.h"
#include "node.h"
#include "Obstacle.h"

void Node::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\ball.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Node::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Node::Update()
{
	// ���b�V���t�B�[���h�����擾
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);

	m_Position.y = meshField->GetHeight(m_Position);
}

void Node::Draw()
{

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);

	if (!camera->CheckView(m_Position))
		return;

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x / 4, m_Scale.y / 4, m_Scale.z / 4);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}