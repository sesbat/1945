#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include <map>
#include"../3rd/Singleton.h"

using namespace sf;
using namespace std;

class SceneMgr : public Singleton<SceneMgr>
{
private:
	map<Scenes, Scene*> sceneMap;
	Scenes currScene;
public:
	bool Init();

	Scene* GetCurrScene();
	Scene* GetScene(Scenes scene);
	void ChangeScene(Scenes scene);

	void Update(float dt);
	void Draw(RenderWindow& window);

};

#define SCENE_MGR (SceneMgr::GetInstance())