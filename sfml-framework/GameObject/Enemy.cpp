#include "Enemy.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/Bullet.h"
#include "../Framework/Framework.h"
#include "Player.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2f pos)
{
	position = pos;
	SetPos(position);
	enemyAlive = true;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
	ShootDelay -= dt;

	if(enemyAlive) 
	{
		if (ShootDelay <= 0.f)
		{
			Fire();
			ShootDelay = 0.2f;
		}
	}

	if (position.x >= 480.f)
	{
		position.x -= 50 * dt;
		SetPos({ position.x , position.y });
	}


	if(enemyAlive) 
	{
		for (auto bullet : player->GetBulletPool()->GetUseList())
		{
			if (GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
			{
				OnCollision(player->GetDamage());
				bullet->SetActive(false);
				if (hp <= 0)
				{
					SetActive(false);
					enemyAlive = false;
				}
			}
		}
	}
	SpriteObj::Update(dt);
}

void Enemy::Release()
{
	SpriteObj::Release();
}

void Enemy::Init()
{
	SpriteObj::Init();
}

void Enemy::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Enemy::OnCollision(int Damage)
{
	hp -= Damage;
}

void Enemy::Fire()
{
	Vector2f startPos = position;
	Bullet* bullet = bulletPool->Get();
	SCENE_MGR->GetCurrScene()->AddGameObj(bullet);
	bullet->Fire(startPos, { 0,1 }, 1000, 500);
}
void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}
