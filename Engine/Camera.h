#pragma once

#include "CoordinateTransformer.h"
#include "Graphics.h"
#include "RectF.h"

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
		drawable.ApplyTransformation(
			Mat3::Rotation(angle) * 
			Mat3::Scale(scale) *
			Mat3::Translation(-pos.x, -pos.y));
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
	float GetAngle() const
	{
		return angle;
	}
	void SetAngle(float angle_in)
	{
		angle = angle_in;
	}
	RectF GetViewprotRect() const
	{
		const float zoom = 1.0f / scale;
		const float diagonal = (
			sq(float(Graphics::ScreenWidth / 2) * zoom) +
			sq(float(Graphics::ScreenHeight / 2) * zoom));
		return RectF::FromCenter(pos, diagonal, diagonal);
	}
private:
	Vec2 pos = {0.0f, 0.0f};
	float scale = 1.0f;
	float angle = 0.0f;
	CoordinateTrasnformer& ct;
};