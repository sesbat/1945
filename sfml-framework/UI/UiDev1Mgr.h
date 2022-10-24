#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"

class UiDev1Mgr
	:public UiMgr
{
protected:

public:
	UiDev1Mgr(Scene* scene);
	~UiDev1Mgr();

	virtual void Init()override;
	virtual void Release();
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

