#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../GameObject/TextObj.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/SoundMgr.h"
#include "../Framework/Utils.h"
#include "../Animation/Animator.h"
#include "../UI/UiDev1Mgr.h"
#include"../Framework/Framework.h"
#include "../Animation/AnimationClip.h"
#include "Scene.h"

SceneDev1::SceneDev1()
	:Scene(Scenes::Dev1)
{
	Init();
}

SceneDev1::~SceneDev1()
{
	Release();
}

void SceneDev1::SetState(States newState)
{
	if (currState == newState)
		return;
	currState = newState;
}

void SceneDev1::OnCompleteJump()
{
	SetState(States::TitleScene);
}

bool SceneDev1::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}

void SceneDev1::Init()
{
	Release();

	animationSprite.setPosition(1280.f/ 2, 480.f);
	Utils::SetOrigin(animationSprite, Origins::MC);
	animationSprite.setScale({ 6,2 });
	animator.SetTarget(&animationSprite);
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("titleScene"));
	{
		AnimationEvent ev;
		ev.clipId = "titleScene";
		ev.frame = 16;
		ev.onEvent = bind(&SceneDev1::OnCompleteJump, this);
		animator.AddEvent(ev);
	}
	titleSprite.setPosition(1280.f / 2, 272.f);
	Utils::SetOrigin(titleSprite, Origins::MC);
	titleSprite.setScale({ 6,1 });
	title.SetTarget(&titleSprite);
	title.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("title"));
	{
		AnimationEvent ev;
		ev.clipId = "title";
		ev.frame = 1;
		ev.onEvent = bind(&SceneDev1::OnCompleteJump, this);
		title.AddEvent(ev);
	}
	mainTex = new SpriteObj();
	mainTex->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titletext.png"));
	mainTex->SetOrigin(Origins::MC);
	mainTex->SetPos({ 1280.f / 2 , 360.f });
	uiObjList.push_back(mainTex);

	titleTex = new TextObj();
	titleTex->SetText("Press to Enter key");
	titleTex->SetPos({ 1280.f / 2, 480.f });
	titleTex->SetFont(*RESOURCE_MGR->GetFont("font/1945.ttf"));
	uiObjList.push_back(titleTex);

	SetState(States::TitleScene);

	uiMgr = new UiDev1Mgr(this);
	uiMgr->Init();

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev1::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}

	Scene::Release();
}

void SceneDev1::Enter()
{
	worldView.setSize(1280,720);
	worldView.setCenter(1280 / 2, 720 / 2);

	animator.Play("titleScene");
	title.Play("title");
}

void SceneDev1::Exit()
{
	uiMgr->Reset();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Num2))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
	}
	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		exit(1);
	}
	switch (currState)
	{
	case States::TitleScene:

		break;
	default:
		break;
	}
	animator.Update(dt);
	Scene::Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(animationSprite);
	window.draw(titleSprite);
	mainTex->Draw(window);
}

