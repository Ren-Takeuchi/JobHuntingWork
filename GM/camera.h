#pragma once

#include "gameObject.h"

class Camera : public GameObject
{
private:

	//D3DXVECTOR3 m_Position; // カメラの位置
	D3DXVECTOR3 m_Target;   // 注視点の位置
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectMatrix;

public:
	void Init();  // 初期化
	void Uninit();// 終了
	void Update();// 更新
	void Draw();  // 描画

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position);

};