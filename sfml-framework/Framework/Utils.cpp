#include "Utils.h"

random_device Utils::rd;
mt19937 Utils::gen(Utils::rd());

void Utils::SetOrigin(Text& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Shape& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Transformable& obj, Origins origin, FloatRect rect)
{
	Vector2f originPos;
	originPos.x = rect.width * ((int)origin % 3) * 0.5f;
	originPos.y = rect.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

int Utils::RandomRange(int min, int maxExclude)
{
	return (gen() % (maxExclude  - min)) + min;
}

float Utils::RandomRange(float min, float max)
{
	uniform_real_distribution<> dist(min, max);
	return dist(gen);
}

float Utils::SqrMagnitude(const Vector2f& vec)
{
	return  (vec.x * vec.x + vec.y * vec.y); 
}

float Utils::Magnitude(const Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);//루트 씌워주는 함수

}

Vector2f Utils::Normalize(const Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return vec;
	return Vector2f(vec.x/mag,vec.y/mag);  //  = vec / mag;
}
