#pragma once


#include <list>
#include <vector>
#include <typeinfo>

#include "gameObject.h"

class Scene
{
protected:
	std::list<GameObject*>  m_GameObject[3]; // STLのリスト構造

public:
	Scene(){}
	virtual ~Scene(){}

	virtual void Init() = 0; // 純粋仮想関数

	template <typename T>// テンプレート関数->ヘッダーでしか作れない
	T* AddGameObject(int Layer)
	{
		T* gameobject = new T();
		gameobject->Init();
		m_GameObject[Layer].push_back(gameobject);

		return gameobject;
	}


	template <typename T>// テンプレート関数->ヘッダーでしか作れない
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))// 型を調べる(RTTI動的型情報)
			{
				return(T*)object;
			}
		}
		return NULL;
	}


	template <typename T>// テンプレート関数->ヘッダーでしか作れない
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;// STLの配列
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
			m_GameObject[i].clear(); // リストのクリア
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) // 範囲forループ 
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
			// ラムダ式
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