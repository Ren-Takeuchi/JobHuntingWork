#pragma once

#include "gameObject.h"

class Sky : public GameObject
{
private:

	class Model* m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:
	void Init();  // 初期化
	void Uninit();// 終了
	void Update();// 更新
	void Draw();  // 描画

};