#include "SpriteObj.h"
#include "../Framework/Utils.h"

SpriteObj::SpriteObj()
{

}

SpriteObj::~SpriteObj()
{

}


void SpriteObj::Draw(RenderWindow& window)
{
	if (enabled)
		window.draw(sprite);
}

void SpriteObj::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}


void SpriteObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

void SpriteObj::SetTextureRect(const IntRect& rect)
{
	sprite.setTextureRect(rect);
}

const IntRect& SpriteObj::GetTextureRect() const
{
	return sprite.getTextureRect();
}

Vector2f SpriteObj::GetSize() const
{
	FloatRect rect = sprite.getLocalBounds();

	return Vector2f(rect.width, rect.height);
}

FloatRect SpriteObj::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position);
}

void SpriteObj::SetAll(Texture& tex, const Vector2f& pos, Origins origin)
{
	sprite.setTexture(tex);
	Object::SetPos(pos);
	sprite.setPosition(position);
	Utils::SetOrigin(sprite, origin);
}
