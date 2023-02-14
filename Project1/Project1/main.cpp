// ----------------------------------------------------------------
// Copyright (C) 2023 MIN U SHIN. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Simulation.h"

int main(int argc, char* argv[])
{
	Simulation sim;
	bool success = sim.Initialize();
	if (success)
	{
		sim.RunLoop();
	}
	sim.Shutdown();
	return 0;
}
