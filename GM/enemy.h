#pragma once

#include "gameObject.h"

constexpr auto X = 16;
constexpr auto Y = 4;

// �L���[
constexpr auto Q = 64;

// �o�H
typedef struct 
{
	int path[X];
	int len;
} Path;

class Enemy : public GameObject
{
private:

	class AnimationModel* m_Model;

	int m_Frame;
	float m_Speed;
	float m_Angel;
	bool isEnemy = false;
	bool isActive;

	Path buff[Q];
	int  front;
	int  rear;

	E_Node m_Node;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	
public:
	void Init();  // ������
	void Uninit();// �I��
	void Update();// �X�V
	void Draw();  // �`��

	int top(Path *p);
	bool visited(Path *p, int x);
	void init_queue(int start);
	Path *deq(void);
	void enq(Path *p, int x);
	bool is_empty(void);
	void bfs(int start, int goal);
};