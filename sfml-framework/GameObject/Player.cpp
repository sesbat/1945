#include "Player.h"
#include "../Framework/InputMgr.h"
#include "../Scene/SceneMgr.h"

Player::Player()
	:level(BulletLevel::LEVEL1),hp(100)
{
}

Player::~Player()
{
}



void Player::Init()
{
	SpriteObj::Init();
}

void Player::Release()
{
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);

	dir.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	dir.y = InputMgr::GetAxisRaw(Axis::Vertical);

	shootDelay -= dt;
	hitDelay -= dt;

	if(shootDelay<=0)
	{
		Fire();
		shootDelay = 0.2f;
	}
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{

	}

	// ����
	//velocity += direction * accelation * dt;
	/*if (Utils::Magnitude(velocity) > speed)
	{
		velocity = Utils::Normalize(velocity) * speed;
	}*/

	/*if (direction.x == 0.f)
	{
		if (velocity.x > 0.f)
		{
			velocity.x -= deaccelation * dt;
			if (velocity.x < 0.f)
				velocity.x = 0.f;
		}
		if (velocity.x < 0.f)
		{
			velocity.x += deaccelation * dt;
			if (velocity.x > 0.f)
				velocity.x = 0.f;
		}
	}

	if (direction.y == 0.f)
	{
		if (velocity.y > 0.f)
		{
			velocity.y -= deaccelation * dt;
			if (velocity.y < 0.f)
				velocity.y = 0.f;
		}
		if (velocity.y < 0.f)
		{
			velocity.y += deaccelation * dt;
			if (velocity.y > 0.f)
				velocity.y = 0.f;
		}
	}
	*/
	Translate(speed * dir * dt);

}

void Player::Draw(RenderWindow& window)
{
	
	SpriteObj::Draw(window);
}

void Player::Fire()
{
	Vector2f startPos = position;
	Bullet* bullet = bulletPool->Get();
	SCENE_MGR->GetCurrScene()->AddGameObj(bullet);
	bullet->Fire(startPos, {0,-1}, 1000, 500);
}
