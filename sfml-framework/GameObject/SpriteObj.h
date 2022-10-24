#pragma once
#include "Object.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"

class SpriteObj :
    public Object
{
protected:
    Sprite sprite;
public:
	SpriteObj();
	virtual ~SpriteObj();

	virtual void Draw(RenderWindow& window) override;

	void SetTexture(Texture& tex);
	void SetOrigin(Origins origin);

	void SetTextureRect(const IntRect& rect);
	const IntRect& GetTextureRect() const;

	Vector2f GetSize()const;
	FloatRect GetGlobalBounds() const;
	Sprite GetSprite() { return sprite; }
	virtual void SetPos(const Vector2f& pos) override;
	void SetAll(Texture& tex, const Vector2f& pos, Origins origin);
};

