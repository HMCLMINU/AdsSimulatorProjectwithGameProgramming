#pragma once
#include "SDL/SDL.h"
#include <string>
#include <vector>
#include <iostream>

class Simtest
{
public:
	Simtest();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	SDL_Window* mWindow;
	bool mIsRunning;
};

