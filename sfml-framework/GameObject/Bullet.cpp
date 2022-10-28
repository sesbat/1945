#include "Bullet.h"
#include "../Framework/Utils.h"
#include "../Framework/SoundMgr.h"
Bullet::Bullet()
	: dir(), speed(0.f), range(0.f)
{
}

Bullet::Bullet(sf::Texture* tex,sf::Vector2f dir, sf::Vector2f pos, sf::IntRect rect)
	:dir(), speed(100.f), range(1000.f)
{
	this->dir = dir;
	sprite.setTexture(*tex);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos);
}

Bullet::~Bullet()
{
}

void Bullet::Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range)
{
	SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
}

void Bullet::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();
}

void Bullet::Release()
{
	SpriteObj::Release();
}

void Bullet::Reset()
{
	dir = { 1, 0 };
	speed = 0.f;
	range = 0.f;
	sprite.setRotation(0.f);
	SetPos({ 0, 0 });

	SpriteObj::Reset();
}

void Bullet::Update(float dt)
{
	SpriteObj::Update(dt);
	//SetPos(position + dir * dt * speed);

	Translate(dir * dt * speed);
	range -= Utils::Magnitude(dir * dt * speed);
}

void Bullet::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}
