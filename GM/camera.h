#pragma once

#include "gameObject.h"

class Camera : public GameObject
{
private:

	//D3DXVECTOR3 m_Position; // �J�����̈ʒu
	D3DXVECTOR3 m_Target;   // �����_�̈ʒu
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectMatrix;

public:
	void Init();  // ������
	void Uninit();// �I��
	void Update();// �X�V
	void Draw();  // �`��

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position);

};