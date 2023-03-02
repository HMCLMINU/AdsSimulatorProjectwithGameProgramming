// ----------------------------------------------------------------
// Copyright (C) 2023 MIN U SHIN. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "Math.h"
#include <vector>
#include <unordered_map>

using namespace std;

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

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//void AddSprite(class SpriteComponent* sprite);
	//void RemoveSprite(class SpriteComponent* sprite);
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
	// Track if we're updating actors right now
	bool mUpdatingActors;
	// Sampling time
	int ts;

	// All the actors in the simulation
	vector<class Actor*> mActors;
	// Any pending actors
	vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	//vector<class SpriteComponent*> mSprites;

	// Simulation specific
	// Position of paddle
	//class Ads* mAv;
	//vector<class Ads*> mSurroundVehicles;
};
