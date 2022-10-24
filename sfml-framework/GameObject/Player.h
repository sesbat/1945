#pragma once
#include "SpriteObj.h"
#include "Bullet.h"
#include "../Framework/ObjectPool.h"

enum class BulletType
{
	LEVEL1,
	LEVEL2,
	LEVEL3,
};

class Player :
    public SpriteObj
{
private:
	Vector2f dir;
	float speed = 1000.f;
	float shootDelay = 0.1f;

	int Damage = 5;
	ObjectPool<Bullet>* bulletPool;
public:
    Player();
    ~Player();

	void SetBulletPool(ObjectPool<Bullet>* ptr) { bulletPool = ptr; }
	ObjectPool<Bullet>* GetBulletPool() { return bulletPool; }

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	int GetDamage() { return Damage; }

	void UpgradeBullet();
	void Fire();
};

