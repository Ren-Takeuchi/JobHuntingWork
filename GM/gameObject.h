#pragma once


// �m�[�h��
enum class E_Node : int
{
	S = 0,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
};


// �N���X�p��
class GameObject
{

protected: // �p����̃N���X����A�N�Z�X�ł���
	bool        m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	E_Node m_Node;

	/*ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;*/

public:
	GameObject() {}// �R���X�g���N�^�@�C���X�^���X(new)��ǂ񂾂Ƃ��Ɏ����I�ɌĂяo�������� �������������������g��
	virtual ~GameObject() {}// �f�X�g���N�^�@delete��ǂ񂾂Ƃ��Ă΂��

	virtual	void Init() = 0;  // �������z�֐�
	virtual void Uninit() = 0; 
	virtual void Update() = 0; 
	virtual void Draw() = 0;   

	// �|�W�V�����擾
	D3DXVECTOR3 GetPosition() { return m_Position; }

	// �m�[�h�擾
	E_Node GetNode() { return m_Node; }

	// �I�u�W�F�N�g�|�W�V�����Z�b�g
	void SetPostion(D3DXVECTOR3 Postion) { m_Position = Postion; }

	// �m�[�h�o�^
	void SetNode(D3DXVECTOR3 Postion, E_Node node)
	{
		m_Position = Postion;
		m_Node = node;
	}

	D3DXVECTOR3 GetObbX() // N
	{
		D3DXMATRIX rot, scale, world, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbZ() // V
	{
		D3DXMATRIX rot, scale, world, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 0.5f;
	}

	D3DXVECTOR3 GetForward() // �O�����x�N�g���擾
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	

	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};