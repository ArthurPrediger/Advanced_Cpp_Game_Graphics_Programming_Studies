#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"

class Drawable
{
public:
	Drawable(const std::vector<Vec2>& model, Color c)
		:
		model(&model),
		c(c)
	{}
	void ApplyTransformation(const Mat3& transformation_in)
	{
		transformation = transformation_in * transformation;
	}
	void Render(Graphics& gfx)
	{
		gfx.DrawClosedPolyline(*model, transformation, c);
	}
private:
	Color c;
	const std::vector<Vec2>* model;
	Mat3 transformation = Mat3::Identity();
};