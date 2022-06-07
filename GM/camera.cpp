#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "scene.h"
#include "camera.h"
#include "player.h"
#include "input.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(-2.0f, 4.0f, 4.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void Camera::Uninit()
{

}

void Camera::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Target = player->GetPosition();

	// トップビュー
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 1.0f, -3.0f);

	//// サードパーソンビュー
	D3DXVECTOR3 forward = player->GetForward();
	m_Position = m_Target + forward * 2.0f+ D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void Camera::Draw()
{
	// ビューマトリクス設定 カメラの設定
	//D3DXMATRIX viewMatrix;
    D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定　どうゆう範囲をレンダリングするか
	//D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&m_ProjectMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectMatrix);
}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invp;

	vp = m_ViewMatrix * m_ProjectMatrix;
	D3DXMatrixInverse(&invp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4]; // ワールドpos

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3( 1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f,-1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3( 1.0f,-1.0f, 1.0f);
    
	//　vposをinvpに入れwposを変換
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invp);

	D3DXVECTOR3 v, v1, v2, v3, v4, n, n1, n2, n3;

	v = Position - m_Position;

	v1 = wpos[0] - m_Position;// 左上
	v2 = wpos[2] - m_Position;// 左下
	v3 = wpos[1] - m_Position;// 右上
	v4 = wpos[3] - m_Position;// 右下

	D3DXVec3Cross(&n, &v1, &v2); //nは内側認識 左
	D3DXVec3Cross(&n1, &v3, &v4);// 右
	D3DXVec3Cross(&n2, &v1, &v3);// 上
	D3DXVec3Cross(&n3, &v2, &v4);// 下

	if (D3DXVec3Dot(&n, &v) < 0.0f)// 内積計算
		return false;
	if (D3DXVec3Dot(&n1, &v) > 0.0f)
		return false;
	if (D3DXVec3Dot(&n2, &v) > 0.0f)
		return false;
	if (D3DXVec3Dot(&n3, &v) < 0.0f)
		return false;

	return true;
}