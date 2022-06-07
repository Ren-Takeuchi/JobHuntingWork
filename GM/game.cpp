
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "polygon2D.h"
#include "camera.h"
#include "explosion.h"
#include "meshField.h"
//#include "field.h"
#include "model.h" // playerの前
#include "player.h"
#include "enemy.h"
#include "Obstacle.h"
#include "node.h"
//#include "bullet.h"
#include "sky.h"
//#include "audio.h"

#include "game.h"

void Game::Init()
{
	//Bullet::Load();
	// 完ぺきではない　コンパイルするとそれぞれに対する関数が作られるためサイズが大きくなる
	AddGameObject<Camera>(0);

	AddGameObject<MeshField>(1);
	//AddGameObject<Field>(1);
	AddGameObject<Sky>(1);
	AddGameObject<Enemy>(1)->SetPostion(D3DXVECTOR3(-6.0f, 0.0f, -6.0f));
	AddGameObject<Player>(1);	
	

	// ウェイポイントのノード設置
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-6.0f, 0.0f, -6.0f),  E_Node::A);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-6.0f, 0.0f,  -2.0f), E_Node::B);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-6.0f, 0.0f,   2.0f), E_Node::C);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-6.0f, 0.0f,   6.0f), E_Node::D);

	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-2.0f, 0.0f, -6.0f), E_Node::E);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-2.0f, 0.0f, -2.0f), E_Node::F);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-2.0f, 0.0f, 2.0f),  E_Node::G);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(-2.0f, 0.0f, 6.0f),  E_Node::F);

	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(2.0f, 0.0f, -6.0f), E_Node::I);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(2.0f, 0.0f, -2.0f), E_Node::J);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(2.0f, 0.0f, 2.0f),  E_Node::K);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3(2.0f, 0.0f, 6.0f),  E_Node::L);

	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3( 6.0f, 0.0f, -6.0f), E_Node::M);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3( 6.0f, 0.0f, -2.0f), E_Node::N);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3( 6.0f, 0.0f, 2.0f),  E_Node::O);
	AddGameObject<Node>(1)->SetNode(D3DXVECTOR3( 6.0f, 0.0f, 6.0f),  E_Node::P);

	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(-10.0f, 0.0f, -10.0f));
	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(15.0f, 0.0f, 15.0f));
	AddGameObject<Obstacle>(1)->SetPostion(D3DXVECTOR3(-15.0f, 0.0f, -15.0f));

	//AddGameObject<Explosion>(1);//->SetPostion;

	//AddGameObject<Polygon2D>(2);


	/*Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\bgm.wav");
	bgm->Play(true);*/
}

void Game::Uninit()
{
	Scene::Uninit();

	//Bullet::Unload();
}

void Game::Update()
{
	Scene::Update();

}