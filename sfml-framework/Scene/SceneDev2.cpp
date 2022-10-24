#include "SceneDev2.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../UI/UiMgr.h"
#include "../UI/UiDev2Mgr.h"
#include "../GameObject/Player.h"
#include "../Framework/ObjectPool.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Enemy.h"

void OnCreateBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet1-4.png"));
	bullet->Init();
}
void OnCreateEnemyBullet(Bullet* bullet)
{
	SceneDev1* scene = (SceneDev1*)SCENE_MGR->GetScene(Scenes::Dev1);
	bullet->SetTexture(*RESOURCE_MGR->GetTexture("graphics/bullet1-1.png"));
	bullet->Init();
}

SceneDev2::SceneDev2()
	:Scene(Scenes::Dev2)
{
	Init();
}

SceneDev2::~SceneDev2()
{
	Release();
}

void SceneDev2::Init()
{
	Release();

	uiMgr = new UiDev2Mgr(this);
	uiMgr->Init();

	player = new Player();
	player->SetTexture(*RESOURCE_MGR->GetTexture("graphics/player1.png"));
	player->SetPos({ 1280.f / 2 - 90, 600.f });
	player->SetOrigin(Origins::MC);
	player->SetBulletPool(&bullets);
	player->Init();
	objList.push_back(player);

	enemy = new Enemy({ 800.f,200.f });
 	enemy->SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss1.png"));
	enemy->SetOrigin(Origins::BC);
	enemy->SetBulletPool(&EnemyBullets);
	enemy->SetPlayer(player);
	enemy->Init();
	objList.push_back(enemy);

	bullets.OnCreate = OnCreateBullet;
	bullets.Init();

	EnemyBullets.OnCreate = OnCreateEnemyBullet;
	EnemyBullets.Init();

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev2::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	bullets.Release();
	Scene::Release();
}

void SceneDev2::Enter()
{
}

void SceneDev2::Exit()
{
	bullets.Reset();
	uiMgr->Reset();
}

void SceneDev2::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Num1))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}
	enemy->Update(dt);
	player->Update(dt);
	Scene::Update(dt);
}

void SceneDev2::Draw(RenderWindow& window)
{
	const auto& bulletList = bullets.GetUseList();
	for (auto bullet : bulletList)
	{
		bullet->Draw(window);
	}
	enemy->Draw(window); 
	player->Draw(window);
	Scene::Draw(window);
}
