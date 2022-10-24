#pragma once

struct PointF
{
	float x;
	float y;

	void operator +(const PointF rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	void operator +(const int value)
	{
		x += value;
		y += value;
	}

	PointF operator +=(const PointF rhs)
	{
		return PointF{ x + rhs.x, y + rhs.y };
	}

	PointF operator +=(const int value)
	{
		return PointF{ x + value, y + value };
	}

};