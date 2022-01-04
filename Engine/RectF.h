#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float leftX, float rightX, float topY, float bottomY);
	RectF(const Vec2& top_left, const Vec2& bottom_right);
	RectF(const Vec2& top_left, float width, float height);
	bool IsOverLapping(const RectF& other) const;
	static RectF FromCenter(const Vec2& center, float halfWidth, float halfHeight);
	RectF GetExpanded(float offset) const;
	Vec2 GetPosition();
public:
	float leftX;
	float rightX;
	float topY;
	float bottomY;
};
