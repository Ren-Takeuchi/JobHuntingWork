#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"
#include "input.h"
#include "game.h"


// ���̎g�����͂킩��₷���D�� "�V���O���g��" �Ƃ����̂��g���ƃQ�[���Ƃ��Ă͗ǂ�
 Scene* Manager::m_Scene; // �ÓI�����o�ϐ��͂������錾���Ȃ��Ƃ����Ȃ�

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
	// �`��̖��߂͂��̒� 
	// �J���� 3D 2D �̏��ŕ`��

	m_Scene->Draw();

	Renderer::End();
}
