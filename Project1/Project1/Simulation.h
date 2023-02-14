// ----------------------------------------------------------------
// Copyright (C) 2023 MIN U SHIN. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <vector>

using namespace std;

struct Vector2 {
	int x, y;
};
// Simulation class
class Simulation
{
public:
	Simulation();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateSimulation();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Sampling time
	int ts;

	// Pong specific
	// Position of paddle
	Vector2 mPaddlePos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
	vector<pair<Vector2, Vector2>> mBallInfo;
};
