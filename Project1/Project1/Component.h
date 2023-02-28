#pragma once

#include <cstdint>

class Component
{
public:
	// Constructor
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(const uint8_t* keyState) {}
	// Called when world transform changes
	virtual void OnUpdateWorldTransform() {}

	int GetUpdateOrder() const { return mUpdateOrder; }
private:
	// Owning actor
	class Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};
