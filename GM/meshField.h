#pragma once

#include "gameObject.h"
#define SIZE 21

class MeshField : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	VERTEX_3D  m_Vertex[SIZE][SIZE];

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_isPass = -1;

public:

	void Init();  // èâä˙âª
	void Uninit();// èIóπ
	void Update();// çXêV
	void Draw();  // ï`âÊ

	float GetHeight(D3DXVECTOR3 Position);

	MeshField* GetMap(D3DXVECTOR3 pos);

};

