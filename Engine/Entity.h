#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"

class Entity
{
public:
	Entity(std::vector<Vec2> model, const Vec2& pos = { 0.0f, 0.0f }, Color c = Colors::Green)
		:
		c(c),
		pos(pos),
		model(std::move(model))
	{}
	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos(const Vec2& newPos)
	{
		pos = newPos;
	}
	void TranslateBy(const Vec2& offset)
	{
		pos += offset;
	}
	float GetScale() const
	{
		return scale;
	}
	void SetScale(float s)
	{
		scale = s;
	}
	void SetColor(Color c_in)
	{
		c = c_in;
	}
	void SetAngle(float a)
	{
		angle = a;
	}
	float GetCAngle() const
	{
		return angle;
	}
	Drawable GetDrawable() const
	{
		Drawable d(model, c);
		d.ApplyTransformation(
			Mat3::Translation(pos.x, pos.y) *
			Mat3::Scale(scale) * 
			Mat3::Rotation(angle));
		return d;
	}
protected:
	void SetModel(std::vector<Vec2> model_in)
	{
		model = std::move(model_in);
	}
private:
	Color c;
	float angle = 0.0f;
	float scale = 1.0f;
	Vec2 pos;
	std::vector<Vec2> model;
};