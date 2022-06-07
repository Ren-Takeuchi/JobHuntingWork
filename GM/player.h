#pragma once

#include "gameObject.h"

class Player : public GameObject
{
private:

	class AnimationModel* m_Model;

	class Audio* m_ShotSE;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Frame;

public:
	void Init();  // ‰Šú‰»
	void Uninit();// I—¹
	void Update();// XV
	void Draw();  // •`‰æ
};