#pragma once

#include "scene.h"

// �}�l�[�W���[�Ƃ����N���X�@(�Q�[���֌W�S��)
class Manager
{
    static class Scene* m_Scene;

public:
	// �N���X�̂Ȃ��ɂ���֐��� "�����o�֐�" "���\�b�h" �Ƃ���
	static void Init();  // ������
	static void Uninit();// �I��
	static void Update();// �X�V
	static void Draw();  // �`��

	static Scene* GetScene() { return m_Scene; }

		template<typename T>
		static void SetScene()
		{
			if (m_Scene)
			{
				m_Scene->Uninit();
				delete m_Scene;
			}

			m_Scene = new T();
			m_Scene->Init();

		}

};