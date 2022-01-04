#pragma once

#include "Entity.h"
#include "Star.h"
#include "RectF.h"

class StarBro : public Entity
{
public:
	StarBro(Vec2 pos, float radius, float innerRatio, int nFlares, float colorFreq, float colorPhase, Color c,
		float radiusFactorAmpliude, float radiusFactorFreq, float radiusFactorPhase)
		:
		Entity(Star::Make(radius, radius* innerRatio, nFlares), pos, c),
		radius(radius),
		colorFreqFactor(colorFreq * 2.0f * 3.14159f),
		colorPhase(colorPhase),
		baseColor(c),
		radiusFactorAmpliude(radiusFactorAmpliude),
		radiusFactorFreq (2.0f * 3.14159f * radiusFactorFreq),
		radiusFactorPhase(radiusFactorPhase)
	{}
	float GetRadius() const
	{
		return radius * GetScale();
	}
	float GetMaxRadius() const
	{
		return radius * (1.0f + radiusFactorAmpliude);
	}
	RectF GetBoundingRect() const
	{
		return RectF::FromCenter(GetPos(), GetRadius(), GetRadius());
	}
	void UpdateTime(float dt)
	{
		time += dt;
		UpdateColor();
		UpdateScale();
	}
private:
	void UpdateColor()
	{
		Color c;
		const int offset = int(127.0f * sin(colorFreqFactor * time + colorPhase)) + 128;
		c.SetR(std::min(baseColor.GetR() + offset, 255));
		c.SetG(std::min(baseColor.GetG() + offset, 255));
		c.SetB(std::min(baseColor.GetB() + offset, 255));
		SetColor(c);
	}
	void UpdateScale()
	{
		const float factor = radiusFactorAmpliude * sin(radiusFactorFreq * time + radiusFactorPhase);
		SetScale(1.0f + factor);
	}
private:
	float radius;
	Color baseColor;
	float colorFreqFactor;
	float colorPhase;
	float time = 0.0f;
	float radiusFactorAmpliude;
	float radiusFactorFreq;
	float radiusFactorPhase;
};
