#pragma once

#include <vector>
#include "Graphics.h"
#include "Vec2.h"
#include "Drawable.h"

class CoordinateTrasnformer
{
public:
	CoordinateTrasnformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void DrawClosedPolyline(Drawable& drawable) const 
	{
		const Vec2 offset = {float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)};
		drawable.ScaleIndependent(1.0f, -1.0f);
		drawable.Translate(offset);
		drawable.Render(gfx);
	}
private:
	Graphics& gfx;
};