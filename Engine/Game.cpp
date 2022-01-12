/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "MathBullshit.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct),
	plank({ 100.0f, 200.0f }, -380.0f, -100.0f, 280.0f, 10.0f),
	spawn(balls, 15.0f, { -200.0f, -250.0f }, -50.0f, 50.0f, 100.0f, 2.0f)
{
	/*std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> xDist(-WorldWidth / 2.0f, WorldWidth / 2.0f);
	std::uniform_real_distribution<float> yDist(-WorldHeight / 2.0f, WorldHeight / 2.0f);
	std::normal_distribution<float> radDist(meanStarRadius, devStarRadius);
	std::normal_distribution<float> ratDist(meanInnerRatio, devInnerRatio);
	std::normal_distribution<float> flareDist(meanFlares, devFlares);
	const Color colors[] = { Colors::White, Colors::Blue, Colors::Green, Colors::Red, Colors::Cyan, Colors::Yellow };
	std::uniform_int_distribution<size_t> colorSampler(0, std::end(colors) - std::begin(colors));
	std::normal_distribution<float> colorFreqDist(meanColorFreq, devColorFreq);
	std::uniform_real_distribution<float> phaseDist(0.0f, 2.0f * 3.14159f);
	std::normal_distribution<float> radiusAmplitudeDist(meanRadiusAmplitude, devRadiusAmplitude);
	std::normal_distribution<float> radiusFreqDist(meanRadiusFreq, devRadiusFreq);

	while (stars.size() < nStars)
	{
		const auto rad = std::clamp(radDist(rng), minStarRadius, maxStarRadius);
		const Vec2 pos = { xDist(rng), yDist(rng) };
		if (std::any_of(stars.begin(), stars.end(), [&](const StarBro& sb)
			{return (sb.GetPos() - pos).Len() < rad + sb.GetMaxRadius(); }))
		{
			continue;
		}

		const auto rat = std::clamp(ratDist(rng), minInnerRatio, maxInnerRatio);
		const Color c = colors[colorSampler(rng)];
		const int nFlares = std::clamp((int)flareDist(rng), minFlares, maxFlares);
		const float colorFreq = std::clamp(colorFreqDist(rng), minColorFreq, maxColorFreq);
		const float colorPhase = phaseDist(rng);
		const float radiusAmplitude = std::clamp(radiusAmplitudeDist(rng), minRadiusAmplitude, maxRadiusAmplitude);
		const float radiusFreq = std::clamp(radiusFreqDist(rng), minRadiusFreq, maxRadiusFreq);
		const float radiusPhase = phaseDist(rng);
		stars.emplace_back(pos, rad, rat, nFlares, colorFreq, colorPhase, c, radiusAmplitude, radiusFreq, radiusPhase);
	}*/
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	const auto plankPts = plank.GetPoints();
	for (auto& ball : balls)
	{
		const auto dy = plankPts.second.y - plankPts.first.y;
		const auto dx = plankPts.second.x - plankPts.first.x;
		const Vec2 ballPos = ball.GetPos();
		Vec2 plankNormal;
		if (dy == 0)
		{
			plankNormal = { 0.0f, ballPos.y > plankPts.first.y ? 1.0f : -1.0f};
		}
		else if (dx == 0.0f)
		{
			plankNormal = { ballPos.x > plankPts.first.x ? 1.0f : -1.0f, 0.0f };
		}
		else
		{
			const auto m = dy / dx;
			const auto w = -1 / m;
			const auto b = plankPts.first.y - m * plankPts.first.x;
			const auto p = ballPos.y - w * ballPos.x;
			const auto x = (p - b) / (m - w);
			const auto y = m * x + b;
			plankNormal = (ballPos - Vec2(x, y)).Normalize();
		}

		if (plankNormal * ball.GetVel() < 0.0f && 
			DistancePointLine(plankPts.first, plankPts.second, ball.GetPos()) < ball.GetRadius())
		{
			const Vec2 w = plank.GetPlankSurfaceVector().GetNormalized();
			const Vec2 v = ball.GetVel();
			ball.SetVel( w * (v * w) * 2.0f - v);
		}

		ball.Update(dt);
	}
	spawn.Update(dt);

	const float speed = 2.0f;
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		plank.MoveFreeY(speed);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		plank.MoveFreeY(-speed);
	}

	const auto new_end = std::remove_if(balls.begin(), balls.end(), 
		[this](const Ball& b)
		{
			return b.GetPos().Len() > maxBallDistance;
		});
	balls.erase(new_end, balls.end());

	/*for (auto& star : stars)
	{
		star.UpdateTime(dt);
	}

	const float speed = 10.0f;
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		cam.MoveBy({ 0.0f, speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		cam.MoveBy({ 0.0f, -speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		cam.MoveBy({ speed, 0.0f });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		cam.MoveBy({ -speed, 0.0f });
	}
	*/
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::WheelUp)
		{
			cam.SetScale(cam.GetScale() * 1.05f);
		}
		else if (e.GetType() == Mouse::Event::WheelDown)
		{
			cam.SetScale(cam.GetScale() * 0.95f);
		}
	}
}

void Game::ComposeFrame()
{
	cam.Draw(plank.GetDrawable());
	for (auto& ball : balls)
	{
		cam.Draw(ball.GetDrawable());
	}
	/*const auto vp = cam.GetViewprotRect();
	for (const auto& star : stars)
	{
		auto d = star.GetDrawable();
		if (star.GetBoundingRect().IsOverLapping(vp))
		{
			cam.Draw(d);
		}
	}*/
}
