#pragma once

#include "gameObject.h"

class Bullet : public GameObject
{
private:


	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:

	//static void Load();
	//static void Unload();


	void Init();  // ������
	void Uninit();// �I��
	void Update();// �X�V
	void Draw();  // �`��

};