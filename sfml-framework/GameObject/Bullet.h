#pragma once
#include "SpriteObj.h"
#include <list>

class Bullet : public SpriteObj
{
protected:
	Vector2f dir;
	float speed;
	float range;

	int Damage = 1;

public:
	Bullet();
	~Bullet();

	void Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range = 0.f);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	int GetDamage() { return Damage; }

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;


};

