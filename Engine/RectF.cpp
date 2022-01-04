#include "RectF.h"

RectF::RectF(float leftX_in, float rightX_in, float topY_in, float bottomY_in)
	:
	leftX (leftX_in),
	rightX (rightX_in),
	topY (topY_in),
	bottomY (bottomY_in)
{
}

RectF::RectF(const Vec2& top_left, const Vec2& bottom_right)
	:
	leftX(top_left.x),
	rightX(bottom_right.x),
	topY(top_left.y),
	bottomY(bottom_right.y)
{
}

RectF::RectF(const Vec2& top_left, float width, float height)
	:
	leftX(top_left.x),
	rightX(top_left.x + width),
	topY(top_left.y),
	bottomY(top_left.y + height)
{
}

bool RectF::IsOverLapping(const RectF& other) const
{
	return leftX < other.rightX && rightX > other.leftX &&
		topY < other.bottomY && bottomY > other.topY;
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfWeight)
{
	const Vec2 half(halfWidth, halfWeight);
	return RectF(center - half, center + half);
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(leftX + offset, rightX - offset, topY + offset, bottomY - offset);
}

Vec2 RectF::GetPosition()
{
	return Vec2((leftX + rightX) / 2, (topY + bottomY) / 2);
}
