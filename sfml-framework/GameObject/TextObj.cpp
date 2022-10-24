#include "TextObj.h"

TextObj::TextObj()
{
}

TextObj::~TextObj()
{
}

void TextObj::SetText(const string& str)
{
	text.setString(str);
}

void TextObj::SetFont(Font& fon)
{
	text.setFont(fon);
}


void TextObj::Init()
{
}

void TextObj::Update(float dt)
{
}

void TextObj::Draw(RenderWindow& window)
{
	window.draw(text);
}

const Text& TextObj::GetText() const
{
	return text;
}


