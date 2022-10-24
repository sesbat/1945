#pragma once
#include "../3rd/Singleton.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2i windowSize;

	// TimeMgr
	Clock clock;
	Time deltaTime;
	float timeScale;
public:
	Framework();
	Framework(int width, int height);
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;
	const Vector2i& GetWindowSize() const;
	RenderWindow& GetWindow();

	bool Init(int width, int height);
	bool Do();
};

#define FRAMEWORK (Framework::GetInstance())