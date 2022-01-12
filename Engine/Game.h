/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <algorithm>
#include "CoordinateTransformer.h"
#include "Star.h"
#include "Camera.h"
#include "StarBro.h"
#include <random>
#include "FrameTimer.h"
#include "Plank.h"
#include "SpawnPoint.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	// world generation parameters
	/*static constexpr float WorldWidth = 10000.0f;
	static constexpr float WorldHeight = 6000.0f;
	static constexpr int nStars = 500;
	static constexpr float meanStarRadius = 160.0f;
	static constexpr float devStarRadius = 90.0f;
	static constexpr float minStarRadius = 40.0f;
	static constexpr float maxStarRadius = 300.0f;
	static constexpr float meanInnerRatio = 0.4f;
	static constexpr float devInnerRatio = 0.25f;
	static constexpr float minInnerRatio = 0.15f;
	static constexpr float maxInnerRatio = 0.8f;
	static constexpr float meanFlares = 6.5f;
	static constexpr float devFlares = 2.0f;
	static constexpr int minFlares = 3;
	static constexpr int maxFlares = 8;
	static constexpr float meanColorFreq = 1.8f;
	static constexpr float devColorFreq = 1.0f;
	static constexpr float minColorFreq = 0.6f;
	static constexpr float maxColorFreq = 4.0f;

	static constexpr float meanRadiusAmplitude = 0.5f;
	static constexpr float devRadiusAmplitude = 0.3f;
	static constexpr float minRadiusAmplitude = 0.1f;
	static constexpr float maxRadiusAmplitude = 0.9f;
	static constexpr float meanRadiusFreq = 1.8f;
	static constexpr float devRadiusFreq = 1.0f;
	static constexpr float minRadiusFreq = 0.6f;
	static constexpr float maxRadiusFreq = 4.0f;*/
	// game objects
	static constexpr float maxBallDistance = 2000.0f;
	FrameTimer ft;
	CoordinateTrasnformer ct;
	Camera cam;
	std::vector<StarBro> stars;
	Plank plank;
	std::vector<Ball> balls;
	SpawnPoint spawn;
	/********************************/
};