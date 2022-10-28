#pragma once
#include "Scene.h"
#include "../Animation/Animator.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../Animation/AnimationClip.h"


class SpriteObj;
class TextObj;
class SceneDev1 : public Scene
{
private:
	
protected:
	Sprite animationSprite;
	Animator animator;

	Sprite titleSprite;
	Animator title;

	SpriteObj* mainTex;
	TextObj* titleTex;

	States currState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
public:
	SceneDev1();
	~SceneDev1();

	void SetState(States newState);

	void OnCompleteJump();

	bool EqualFloat(float a, float b);

	void Init() ;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

};

