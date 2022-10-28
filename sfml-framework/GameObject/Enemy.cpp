#include "Enemy.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/Bullet.h"
#include "../Framework/Framework.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "../Animation/Animator.h"

void addBullet(sf::VertexArray* v, EnemyBullet* bul, size_t index) {

	// Get the quad contained in the vertex array
	sf::Vertex* quad = &(*v)[index * 4];
	sf::Sprite spr = bul->GetSprite();

	// Set the position of the sprite
	quad[0].position = sf::Vector2f(spr.getPosition().x, spr.getPosition().y);
	quad[1].position = sf::Vector2f(spr.getPosition().x + spr.getTextureRect().width,
		spr.getPosition().y);
	quad[2].position = sf::Vector2f(spr.getPosition().x + spr.getTextureRect().width,
		spr.getPosition().y + spr.getTextureRect().height);
	quad[3].position = sf::Vector2f(spr.getPosition().x, spr.getPosition().y +
		spr.getTextureRect().height);

	// Set the texture of the sprite
	quad[0].texCoords = sf::Vector2f(spr.getTextureRect().left, spr.getTextureRect().top);
	quad[1].texCoords = sf::Vector2f(spr.getTextureRect().left + spr.getTextureRect().width,
		spr.getTextureRect().top);
	quad[2].texCoords = sf::Vector2f(spr.getTextureRect().left + spr.getTextureRect().width,
		spr.getTextureRect().top + spr.getTextureRect().height);
	quad[3].texCoords = sf::Vector2f(spr.getTextureRect().left, spr.getTextureRect().top +
		spr.getTextureRect().height);
}
Enemy::Enemy()
{

}
Enemy::Enemy(Vector2f pos)
	: vertices(sf::Quads, totalBullets),border(0, 0, 1280, 720), accelation(3), deaccelation(3),speed(10)
{
	
	position = pos;
	SetPos(position);
	enemyAlive = true;

	hpBarSize.x = hp;
	hpBarSize.y = 10;
	hpBar.setFillColor(Color::Red);
	hpBar.setPosition({1280/2,30});
	//for (size_t i = 0; i < totalBullets; i++) {
	//	bullets[i] = NULL;
	//	bullets[i]->SetOrigin(Origins::MC);
	//}

	tex.loadFromFile("graphics/sprites.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
	if (GetPos().y >= 450.f)
	{
		direction.y = -1.f;
	}
	else
	{
		direction.y = 0;
	}
	if (GetPos().x >= 800.f)
	{
		direction.x = -1.f;
	}
	if (GetPos().x <= 480.f)
	{
		direction.x = 1.f;
	}
	velocity += direction * accelation * dt;
	if (Utils::Magnitude(velocity) > speed)
	{
		velocity = Utils::Normalize(velocity) * speed;
	}

	if (direction.x == 0.f)
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

	Translate(speed * velocity * dt);

	for (size_t i = 0; i < totalBullets; i++) {
		if (bullets[i] != NULL && bullets[i]->GetActive()) {
			bullets[i]->Update(dt * 1000.f);
			sf::Vertex* quad = &vertices[i * 4];
			sf::Sprite* spr = bullets[i]->GetSpritePtr();
			quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
			quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y);
			quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y + spr->getTextureRect().height);
			quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
		}
	}

	if(enemyAlive) 
	{
		
		// Add new red bullet
		if (counterTime > bulletTime && counterWave < 1) {
			// Reset the number of bullet when the max is reached
			if (numBullet == maxBullets) {
				numBullet = 0;
				counterWave++;
			}

			// Delete the previous bullet
			if (bullets[numBullet] != NULL) {
				delete(bullets[numBullet]);
				bullets[numBullet] = NULL;
			}

			// Calculate the coordinate of the velocity vector
			float x = r * cos((size_t)(numBullet % 180) / Pi);
			float y = r * sin((size_t)(numBullet % 180) / Pi);

			EnemyBullet* bul = new EnemyBullet
			(&tex, sf::Vector2f(x * 0.01, y * 0.01), { GetPos().x - 8,GetPos().y - 8 }, sf::IntRect(0, 64, 16, 16));
			bullets[numBullet] = bul;
			addBullet(&vertices, bul, numBullet);

			// update number and counter
			numBullet++;
			counterTime = counterTime - bulletTime;
		}

		// Add new blue bullet
		if (counterTime2 > bulletTime2 && counterWave2 < 3)
		{
			for (size_t i = 0; i < 45; i++) {
				float y = r * cos((size_t)i / (Pi / 2));
				float x = r * sin((size_t)i / (Pi / 2));
				EnemyBullet* bul = new EnemyBullet(&tex, sf::Vector2f(x * 0.01, y * 0.01),
					{GetPos().x - 32, GetPos().y - 32}, sf::IntRect(128, 0, 64, 64));

				if (numBullet2 == maxBullets) {
					numBullet2 = 0;
					counterWave2++;
				}

				if (bullets[maxBullets + numBullet2] != NULL) {
					delete(bullets[maxBullets + numBullet2]);
					bullets[maxBullets + numBullet2] = NULL;
				}
				bullets[maxBullets + numBullet2] = bul;
				addBullet(&vertices, bul, maxBullets + numBullet2);
				numBullet2++;
				counterTime2 = counterTime2 - bulletTime2;
				BlueBullet = 5.f;
			}
			
		}

		// Add new purple bullet
		if (counterTime3 > bulletTime3) {
			for (size_t i = 0; i < 10; i++) {
				float y = r * cos((size_t)rand() % 180 / (Pi));
				float x = r * sin((size_t)rand() % 180 / (Pi));

				EnemyBullet* bul = new EnemyBullet(&tex, sf::Vector2f(x * 0.01, y * 0.01),
					{ GetPos().x - 4,GetPos().y - 4 }, sf::IntRect(0, 80, 8, 8));

				if (numBullet3 == 14 * maxBullets) {
					numBullet3 = 0;
					counterWave3++;
				}

				if (bullets[2 * maxBullets + numBullet3] != NULL) {
					delete(bullets[2 * maxBullets + numBullet3]);
					bullets[2 * maxBullets + numBullet3] = NULL;
				}

				bullets[2 * maxBullets + numBullet3] = bul;
				addBullet(&vertices, bul, 2 * maxBullets + numBullet3);
				numBullet3++;
				counterTime3 = counterTime3 - bulletTime3;
			}
		}


		/**/
		for (size_t i = 0; i < totalBullets; i++) {
			if (bullets[i] != NULL) {
				if (!border.intersects(bullets[i]->GetSpritePtr()->getGlobalBounds()))
				{
					delete bullets[i];
					bullets[i] = NULL;
				}
			}
		}

		counterTime = counterTime + dt;
		counterTime2 = counterTime2 + dt * 100.f;
		counterTime3 = counterTime3 + dt * 1000.f;


		/*if(enemyAlive)
		{
			if (ShootDelay <= 0.f)
			{
				Fire();
				ShootDelay = 0.2f;
			}
		}*/
		
		

	/*	if (position.x >= 640.f)
		{
			position.x -= 50 * dt;
			SetPos({ position.x , position.y });
		}
	}*/
	
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
						enemyAlive = false;
					}
				}
			}
		}

	states.transform = transform;
	states.texture = &tex;
	SpriteObj::Update(dt);
	}
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
	if(enemyAlive) {
		SpriteObj::Draw(window);
	}

	window.draw(vertices, states);
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
