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
#include "../Framework/Framework.h"
#include "../Animation/Animator.h"

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

	canExplosion = true;

	uiMgr = new UiDev2Mgr(this);
	uiMgr->Init();

	player = new Player();
	player->SetTexture(*RESOURCE_MGR->GetTexture("graphics/player1.png"));
	player->SetPos({ 1280.f/ 2 , 600.f });
	player->SetOrigin(Origins::MC);
	player->SetBulletPool(&bullets);
	player->Init();
	objList.push_back(player);

	enemy = new Enemy({ 800.f,1200.f });
 	enemy->SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss1.png"));
	enemy->SetOrigin(Origins::BC);
	//enemy->SetBulletPool(&EnemyBullets);
	enemy->SetPlayer(player);
	enemy->Init();
	objList.push_back(enemy);

	bullets.OnCreate = OnCreateBullet;
	bullets.Init();


	explosionSprite.setPosition(enemy->GetPos().x, enemy->GetPos().y-50);
	//Utils::SetOrigin(explosionSprite, Origins::BC);
	explosionSprite.setScale({ 4,4 });
	explosion.SetTarget(&explosionSprite);
	explosion.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("explosion"));
	{
		AnimationEvent ev;
		ev.clipId = "explosion";
		ev.frame = 15;
		ev.onEvent = bind(&SceneDev2::OnCompleteExplosion, this);
		explosion.AddEvent(ev);
	}

	/*EnemyBullets.OnCreate = OnCreateEnemyBullet;
	EnemyBullets.Init();*/

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
	worldView.setSize(1280, 720);
	worldView.setCenter(1280 / 2, 720 / 2);
}

void SceneDev2::Exit()
{
	bullets.Reset();
	uiMgr->Reset();
}

void SceneDev2::Update(float dt)
{
	//explosionSprite.setPosition(enemy->GetPos());
	if (InputMgr::GetKeyDown(Keyboard::Num1))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}
	for (auto bullet : bullets.GetUseList())
	{
		if (bullet->GetPos().y <= -50)
		{
			objList.remove(bullet);
			bullet = NULL;
		}
	}
	if (enemy->GetHp()<=0&&canExplosion)
	{
		explosion.Play("explosion");
		canExplosion = false;
	}
	
	explosionSprite.setPosition
	(enemy->GetPos().x, enemy->GetPos().y - 50);
	explosion.Update(dt);
	Scene::Update(dt);

}

void SceneDev2::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(explosionSprite);

	const auto& bulletList = bullets.GetUseList();
	for (auto bullet : bulletList)
	{
		bullet->Draw(window);
	}
}
void SceneDev2::SetState(States newState)
{
	if (currState == newState)
		return;
	currState = newState;
}
void SceneDev2::OnCompleteExplosion()
{
	SetState(States::Explosion);
}

