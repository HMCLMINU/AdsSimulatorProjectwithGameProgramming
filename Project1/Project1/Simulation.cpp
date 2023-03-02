// ----------------------------------------------------------------
// Copyright (C) 2023 MIN U SHIN. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Simulation.h"
#include <GL/glew.h>
#include <algorithm>
#include "Actor.h"
#include "Ads.h"
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
	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
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
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
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
	/*SDL_Rect ego{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		carH,
		static_cast<int>(carW)
	};
	SDL_SetRenderDrawColor(mRenderer, 76, 153, 0, 255);
	SDL_RenderFillRect(mRenderer, &ego);*/
	
	// Draw SV - Orange
	/*for (int i = 0; i < mBallInfo.size(); i++) {
		SDL_Rect sv{
			static_cast<int>(mBallInfo[i].first.x - thickness / 2),
			static_cast<int>(mBallInfo[i].first.y - thickness / 2),
			carH,
			carW
		};
		SDL_SetRenderDrawColor(mRenderer, 255, 165, 0, 255);
		SDL_RenderFillRect(mRenderer, &sv);
	}*/
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Simulation::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Simulation::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Simulation::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	// Is it in actors?
	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.begin()) {
		// Swap to end of vector and pop off
		iter_swap(iter, mPendingActors.end() - 1);
		mActors.pop_back();
	}
}