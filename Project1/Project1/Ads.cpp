#include "Ads.h"
#include "Simulation.h"

Ads::Ads(Simulation* simulation)
	:Actor(simulation)
	, mIsSurroundAds(false)
{

}

void Ads::UpdateActor(float deltaTime)
{
	// To do
	mIsSurroundAds = false;
}

void Ads::ActorInput(const uint8_t* keyState)
{
	// To do
	mIsSurroundAds = false;
}