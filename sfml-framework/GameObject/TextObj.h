#pragma once
#include "Object.h"
#include "../Framework/ResourceMgr.h"
class TextObj : public Object
{
protected:
	Text text;
public:
	TextObj();
	~TextObj();

	void SetText(const string& str);
	void SetFont(Font& fon);

	virtual void Init()override;
	virtual void Update(float dt)override;
	virtual void Draw(RenderWindow& window)override;
	const Text& GetText()const;
};

