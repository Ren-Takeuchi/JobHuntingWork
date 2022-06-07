#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

#include "meshField.h"
#include "camera.h"
#include "AnimationModel.h"
#include "player.h"
#include "enemy.h"
#include "node.h"
#include "Obstacle.h"

#include "scene.h"

constexpr auto FRONT_FRAME = 0.3f;

void Enemy::Init()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Akai_Idle.fbx");
	m_Model->LoadAnimaiton("asset\\model\\Unarmed Idle 01.fbx", "Idle");

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.02f, 0.02f, 0.02f);

	m_Frame = 0;
	m_Speed = 0.03f;
	m_Angel = 0.03f;


	Scene* scene = Manager::GetScene();
	std::vector<Node*> List = scene->GetGameObjects<Node>(1);

	//for (Node* node : List)
	//{

	//	auto type = List;

	//	auto m_Node = node->GetNode();

	//	// 一番近いノードのタイプが同じのを探す
	//	if(m_Node == type)
	//	{
	//		// ノードのポジションを入れる
	//		D3DXVECTOR3 np = node->GetPosition();
	//		scene->AddGameObject<Enemy>(1);
	//	}
	//}


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	m_Frame++;
	m_Model->Update("Idle", m_Frame);


	Scene* scene = Manager::GetScene();

	// メッシュフィールド高さ取得
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);

	m_Position.y = meshField->GetHeight(m_Position);


	Player* player = Manager::GetScene()->GetGameObject<Player>(1);

	D3DXVECTOR3 PlayerPos = player->GetPosition();
	D3DXVECTOR3 lastPos = m_Position;

	D3DXVECTOR3 Direction = PlayerPos - m_Position; //プレイヤーとキャラの幅を求める
	float directionLenx;

	directionLenx = D3DXVec3Length(&Direction);
	Direction /= directionLenx;// 正規化


	if (m_Position > PlayerPos) // 移動
	{
		m_Position = m_Position + Direction * m_Speed;
	}
	
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



}

void Enemy::Draw()
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
	D3DXMatrixScaling(&scale, m_Scale.x / 4, m_Scale.y / 4, m_Scale.z / 4);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}



int Enemy::top(Path *p)
{
	return p->path[p->len - 1];
}

bool Enemy::visited(Path *p, int x)
{
	for (int i = 0; i < p->len; i++) {
		if (p->path[i] == x) return true;
	}
	return false;
}

void Enemy::init_queue(int start)
{
	buff[0].path[0] = start;
	buff[0].len = 1;
	rear = 1;
}

Path *Enemy::deq(void)
{
	return &buff[front++];
}

void Enemy::enq(Path *p, int x)
{
	buff[rear] = *p;
	buff[rear].path[p->len] = x;
	buff[rear++].len++;
}

bool Enemy::is_empty(void)
{
	return front == rear;
}

//void Enemy::bfs(int start, int goal)
//{
//	init_queue(start);
//	while (!is_empty()) {
//		Path *p = deq();
//		int x = top(p);
//		if (x == goal) {
//		}
//		else {
//			for (int i = 0; i < Y; i++) {
//				int y = adjacent[x][i];
//				if (y == 0) break;
//				if (!visited(p, y)) enq(p, y);
//			}
//		}
//	}
//}