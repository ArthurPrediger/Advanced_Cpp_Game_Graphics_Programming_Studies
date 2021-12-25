#pragma once

#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera(CoordinateTrasnformer& ct)
		:
		ct(ct)
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy(const Vec2& offset)
	{
		pos += offset;
	}
	void MoveTo(const Vec2& pos_in)
	{
		pos = pos_in;
	}
	void Draw(Drawable& drawable) const
	{
		drawable.Translate(-pos);
		drawable.Scale(scale);
		ct.DrawClosedPolyline(drawable);
	}
	float GetScale() const
	{
		return scale;
	}
	void SetScale(float scale_in)
	{
		scale = scale_in;
	}
private:
	Vec2 pos = {0.0f, 0.0f};
	float scale = 1.0f;
	CoordinateTrasnformer& ct;
};