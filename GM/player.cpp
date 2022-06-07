#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "scene.h"

#include "AnimationModel.h"
#include "camera.h"
#include "meshField.h"
#include "player.h"
#include "Obstacle.h"
#include "enemy.h"
#include "bullet.h"

#define FRONT_FRAME 0.3f

static Player player;


void Player::Init()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Akai_Idle.fbx");
	m_Model->LoadAnimaiton("asset\\model\\Unarmed Idle 01.fbx", "Idle");
	m_Model->LoadAnimaiton("asset\\model\\Run.fbx", "Run");
	m_Model->LoadAnimaiton("asset\\model\\Catwalk Walk Forward HighKnees.fbx", "Walk");
	m_Model->LoadAnimaiton("asset\\model\\Hurricane Kick (1).fbx", "Kick");
	m_Model->LoadAnimaiton("asset\\model\\Standing Walk Back.fbx", "Back Walk");
	m_Model->LoadAnimaiton("asset\\model\\Standing Run Back.fbx", "Back Run");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
    m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale    = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Scene* scene = Manager::GetScene();

	//m_ShotSE = scene->AddGameObject<Audio>(2);
	//m_ShotSE->Load("asset\\audio\\魔王魂  銃01.wav");

}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	m_Frame++;

	D3DXVECTOR3 lastPos = m_Position;

	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= 0.08f;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 0.08f;
	}

	D3DXVECTOR3 forward = GetForward();

	if (Input::GetKeyPress('W') && Input::GetKeyPress('F'))
	{
		m_Position -= forward * 0.03f;
		m_Model->Update("Run", m_Frame);
	}
	else if (Input::GetKeyPress('W') && Input::GetKeyPress('K'))
	{
		m_Position -= forward * 0.1f;
		m_Model->Update("Kick", m_Frame);
	}
	else if (Input::GetKeyPress('W'))
	{
		m_Position -= forward * 0.008f;
	    m_Model->Update("Walk", m_Frame);
	}
	else if (Input::GetKeyPress('K'))
	{
		m_Model->Update("Kick", m_Frame);
	}
	else
	{
		m_Model->Update("Idle", m_Frame);
	}

	if (Input::GetKeyPress('S') && Input::GetKeyPress('F'))
	{
		m_Position += forward * 0.01f;
		m_Model->Update("Back Run", m_Frame);
	}
	else if (Input::GetKeyPress('S'))
	{
		m_Position += forward * 0.006f;
		m_Model->Update("Back Walk", m_Frame);
	}

	Scene* scene = Manager::GetScene();
	std::vector<Obstacle*> obstacleList = scene->GetGameObjects<Obstacle>(1);

	for (Obstacle* obstacle : obstacleList)
	{

		D3DXVECTOR3 obstaclePosition = obstacle->GetPosition();
		D3DXVECTOR3 direction = m_Position - obstaclePosition;

		D3DXVECTOR3 obbx, obbz;
		float obbLenx, obbLenz;

		obbx = obstacle->GetObbX();
		obbLenx = D3DXVec3Length(&obbx); // X方向の箱の半分の長さを求めている
		obbx /= obbLenx; // 正規化の計算

		obbz = obstacle->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz; // 正規化の計算

		float lenX, lenZ;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);

		if (fabs(lenX) < obbLenx + FRONT_FRAME && fabs(lenZ) < obbLenz + FRONT_FRAME) // fabs 絶対値
		{
			m_Position = lastPos;
			return;
		}
	}



	 //メッシュフィールド高さ取得
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);

	m_Position.y = meshField->GetHeight(m_Position);

	//if (Input::GetKeyTrigger(VK_SHIFT))
	//{
	//	Scene* scene = Manager::GetScene();
	//	scene->AddGameObject<Bullet>(1)->SetPostion(m_Position);
	//}


}

void Player::Draw()
{
	// 視錐台カリング
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
	D3DXMatrixScaling(&scale, m_Scale.x / 4, m_Scale.y / 4 , m_Scale.z / 4);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}