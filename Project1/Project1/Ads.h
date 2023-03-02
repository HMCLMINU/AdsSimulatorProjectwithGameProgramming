#pragma once
#include "Actor.h"

class Ads : public Actor
{
public:
	Ads(class Simulation* simulation);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	bool mIsSurroundAds;
};

