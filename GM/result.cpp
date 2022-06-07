
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "result.h"
#include "resultPolygon2D.h"

#include "title.h"

void Result::Init()
{
	AddGameObject<ResultPolygon2D>(2);
}

void Result::Uninit()
{
	Scene::Uninit(); // �p�����N���X�̃��\�b�h�Ăяo��
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}
