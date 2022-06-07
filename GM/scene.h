#pragma once


#include <list>
#include <vector>
#include <typeinfo>

#include "gameObject.h"

class Scene
{
protected:
	std::list<GameObject*>  m_GameObject[3]; // STL�̃��X�g�\��

public:
	Scene(){}
	virtual ~Scene(){}

	virtual void Init() = 0; // �������z�֐�

	template <typename T>// �e���v���[�g�֐�->�w�b�_�[�ł������Ȃ�
	T* AddGameObject(int Layer)
	{
		T* gameobject = new T();
		gameobject->Init();
		m_GameObject[Layer].push_back(gameobject);

		return gameobject;
	}


	template <typename T>// �e���v���[�g�֐�->�w�b�_�[�ł������Ȃ�
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))// �^�𒲂ׂ�(RTTI���I�^���)
			{
				return(T*)object;
			}
		}
		return NULL;
	}


	template <typename T>// �e���v���[�g�֐�->�w�b�_�[�ł������Ȃ�
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;// STL�̔z��
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	/*void RemoveGemeObject(GameObject* Object)
	{
		Object->Uninit();
		m_GameObject.erase(Object);
		delete Object;
	}*/

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();

				delete object;
			}
			m_GameObject[i].clear(); // ���X�g�̃N���A
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) // �͈�for���[�v 
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
			// �����_��
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

};