#pragma once
#include "Scene.h"
#include "../Framework/ObjectPool.h"

class Player;
class Enemy;
class Bullet;
class SceneDev2 : public Scene
{
private:
	Player* player;
	Enemy* enemy;

	ObjectPool<Bullet> bullets;
	ObjectPool<Bullet> EnemyBullets;
public:
	SceneDev2();
	~SceneDev2();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

