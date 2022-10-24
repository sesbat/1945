#include "UiDev1Mgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Scene/SceneDev1.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"


UiDev1Mgr::UiDev1Mgr(Scene* scene)
	:UiMgr(scene)
{
}

UiDev1Mgr::~UiDev1Mgr()
{
}

void UiDev1Mgr::Init()
{
	UiMgr::Init();
}

void UiDev1Mgr::Release()
{
	UiMgr::Release();
}

void UiDev1Mgr::Reset()
{
	UiMgr::Reset();
}

void UiDev1Mgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void UiDev1Mgr::Draw(RenderWindow& window)
{
	UiMgr::Draw(window);
}