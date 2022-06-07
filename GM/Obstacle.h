#pragma once
#include "gameObject.h"

class Obstacle : public GameObject
{
private:

	class Model* m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;


public:
	void Init();  // ‰Šú‰»
	void Uninit();// I—¹
	void Update();// XV
	void Draw();  // •`‰æ


};