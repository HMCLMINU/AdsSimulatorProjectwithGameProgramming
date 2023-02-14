// ----------------------------------------------------------------
// Copyright (C) 2023 MIN U SHIN. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Simulation.h"
#include <iostream>

using namespace std;

const int thickness = 75; // 3.75m * 2 road
const int carH = 25;
const int carW = 45;
const float paddleH = 100.0f;

Simulation::Simulation()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,ts(10) // 10ms sampling rate
{
	//
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -300.0f;
	mBallVel.y = 335.0f;
	mBallInfo.push_back({ mBallPos, mBallVel });

	mBallPos.x = 700.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = 300.0f;
	mBallVel.y = 335.0f;

	mBallInfo.push_back({ mBallPos, mBallVel });
}

bool Simulation::Initialize()
{	
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"ADS Sim test world", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);
	
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Simulation::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateSimulation();
		GenerateOutput();
	}
}

void Simulation::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Simulation::UpdateSimulation()
{
	// Wait until 10ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + ts))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//cout << deltaTime << endl;
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	// To Do:
	// Update Ego position based on velocity
	
	// To Do:
	// Update SV position based on velocity
	

}

void Simulation::GenerateOutput()
{

	// Set draw color to black
	SDL_SetRenderDrawColor(
		mRenderer,
		33,		// R
		33,		// G 
		33,	    // B
		150		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	// TO DO: Draw road, white
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw vertical 1st straight road
	SDL_Rect road{
		512,			// Top left x
		0,			    // Top left y
		thickness,		// Width
		768         	// Height
	};
	SDL_RenderFillRect(mRenderer, &road);
	
	// Draw vertical 2nd straight road
	road.x = 200;
	road.y = 0;
	road.w = thickness;
	road.h = 768;
	SDL_RenderFillRect(mRenderer, &road);

	// Draw vertical 3rd straight road
	road.x = 800;
	road.y = 0;
	road.w = thickness;
	road.h = 768;
	SDL_RenderFillRect(mRenderer, &road);

	// Draw 1st horizontal road
	road.x = 0;
	road.y = 768/2 + 150;
	road.w = 1024;
	road.h = thickness;
	SDL_RenderFillRect(mRenderer, &road);
	
	// Draw 2nd horizontal road
	road.x = 0;
	road.y = 768/2 - 150;
	road.w = 1024;
	road.h = thickness;
	SDL_RenderFillRect(mRenderer, &road);
	
	// Draw Ego - Green
	SDL_Rect ego{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		carH,
		static_cast<int>(carW)
	};
	SDL_SetRenderDrawColor(mRenderer, 76, 153, 0, 255);
	SDL_RenderFillRect(mRenderer, &ego);
	
	// Draw SV - Orange
	for (int i = 0; i < mBallInfo.size(); i++) {
		SDL_Rect sv{
			static_cast<int>(mBallInfo[i].first.x - thickness / 2),
			static_cast<int>(mBallInfo[i].first.y - thickness / 2),
			carH,
			carW
		};
		SDL_SetRenderDrawColor(mRenderer, 255, 165, 0, 255);
		SDL_RenderFillRect(mRenderer, &sv);
	}
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Simulation::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
