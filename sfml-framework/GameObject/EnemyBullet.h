#pragma once
#include "SpriteObj.h"
#include <SFML\Graphics.hpp>
class EnemyBullet
:public SpriteObj{
public:
	EnemyBullet(sf::Texture* tex, sf::Vector2f vel, sf::Vector2f pos, sf::IntRect rect) {
		this->vel = vel;
		SetTexture(*tex);
		SetTextureRect(rect);
		SetPos(pos);
	}

	// Update the position of the bullet
	virtual void Update(float dt) override
	{
		SetPos({ GetPos().x + (dt * vel.x), GetPos().y + (dt * vel.y)});
		//sprite.setPosition({ sprite.getPosition().x + (dt * vel.x), sprite.getPosition().y + (dt * vel.y) })
		//SetPos(position + dir * dt * speed);

		SpriteObj::Update(dt);
	}
	/*virtual void Draw(RenderWindow& window)
	{
		SpriteObj::Draw(window);
	}*/

private:
	sf::Vector2f vel;
};