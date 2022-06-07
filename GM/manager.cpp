#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"
#include "input.h"
#include "game.h"


// この使い方はわかりやすさ優先 "シングルトン" というのを使うとゲームとしては良い
 Scene* Manager::m_Scene; // 静的メンバ変数はもう一回宣言しないといけない

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

   /* m_Scene = new Game();
	m_Scene->Init();*/

	SetScene<Game>();

}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	
	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	// 描画の命令はこの中 
	// カメラ 3D 2D の順で描画

	m_Scene->Draw();

	Renderer::End();
}
