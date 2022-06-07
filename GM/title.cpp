
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "title.h"
#include  "titlePolygon2D.h"

#include "game.h"

void Title::Init()
{
	AddGameObject<TitlePolygon2D>(2);
}

void Title::Uninit()
{
	Scene::Uninit(); // �p�����N���X�̃��\�b�h�Ăяo��
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Game>();
	}
}
