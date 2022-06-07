#pragma once

#include "gameObject.h"

class Polygon2D : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:

	void Init();  // 初期化
	void Uninit();// 終了
	void Update();// 更新
	void Draw();  // 描画

}; //class 作ったら終わりにセミコロン