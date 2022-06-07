#pragma once

#include "scene.h"

// マネージャーというクラス　(ゲーム関係全般)
class Manager
{
    static class Scene* m_Scene;

public:
	// クラスのなかにある関数は "メンバ関数" "メソッド" という
	static void Init();  // 初期化
	static void Uninit();// 終了
	static void Update();// 更新
	static void Draw();  // 描画

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