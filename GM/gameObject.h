#pragma once


// ノード数
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


// クラス継承
class GameObject
{

protected: // 継承先のクラスからアクセスできる
	bool        m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	E_Node m_Node;

	/*ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;*/

public:
	GameObject() {}// コンストラクタ　インスタンス(new)を読んだときに自動的に呼び出されるもの 何か初期化したい時使う
	virtual ~GameObject() {}// デストラクタ　deleteを読んだとき呼ばれる

	virtual	void Init() = 0;  // 純粋仮想関数
	virtual void Uninit() = 0; 
	virtual void Update() = 0; 
	virtual void Draw() = 0;   

	// ポジション取得
	D3DXVECTOR3 GetPosition() { return m_Position; }

	// ノード取得
	E_Node GetNode() { return m_Node; }

	// オブジェクトポジションセット
	void SetPostion(D3DXVECTOR3 Postion) { m_Position = Postion; }

	// ノード登録
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

	D3DXVECTOR3 GetForward() // 前方向ベクトル取得
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