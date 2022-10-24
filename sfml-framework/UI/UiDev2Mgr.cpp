#include "UiDev2Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scene/SceneDev2.h"
#include "../Framework/InputMgr.h"


UiDev2Mgr::UiDev2Mgr(Scene* scene)
	: UiMgr(scene)
{
}

UiDev2Mgr::~UiDev2Mgr()
{
}

void UiDev2Mgr::Init()
{
	UiMgr::Init();
}

void UiDev2Mgr::Release()
{
	UiMgr::Release();
}

void UiDev2Mgr::Reset()
{
	UiMgr::Reset();
}

void UiDev2Mgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void UiDev2Mgr::Draw(RenderWindow& window)
{
	UiMgr::Draw(window);
}
