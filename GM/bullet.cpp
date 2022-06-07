#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"

#include "explosion.h"
#include "model.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"

//Model* Bullet::m_Model; // スタティックメンバ変数はcppで再度宣言が必要

//
//void  Bullet::Load()
//{
////	m_Model = new Model();
////	m_Model->Load("asset\\model\\torus.obj");
////}
//
//void Bullet::Unload()
//{
//	//m_Model->Unload();
//	//delete m_Model;
//}



void Bullet::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void Bullet::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Update()
{
	// 弾発射

	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	D3DXVECTOR3 forward = player->GetForward();

	m_Position += forward * 0.2f;

	// ある一定の距離で球消滅

	if (m_Position.x > 30.0f || m_Position.x < -30.0f || m_Position.z > 30.0f || m_Position.z < -30.0f)
	{
		SetDestroy();
		return;
	}

	// enemyが消える処理

	Scene* scene = Manager::GetScene();
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);

	for (Enemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float lenght = D3DXVec3Length(&direction);

		if (lenght < 2.0f)
		{
			scene->AddGameObject<Explosion>(1)->SetPostion(enemyPosition);

			enemy->SetDestroy();
			SetDestroy();
			return;
		}
	}
}

void Bullet::Draw()
{

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	//m_Model->Draw();
}