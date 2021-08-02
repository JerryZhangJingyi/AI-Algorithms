
#pragma once

#include "Types.h"
class Boid
{
private:
	float width = 10.0f;
	float radius = width / 2.0f;
	rigibody rigid;
	KinematicOutput kinematicInput;
	DynamicOutput dynamicInput;


	float minWidth = 0.0f;
	float maxWidth = 521.0f;

	float minHeight = 0.0f;
	float maxHeight = 448.0f;

public:
	float maxSpeed = 75.0f;
	float maxAcc = 45.0f;

	float maxRotation = 0.5f;
	float maxAngularAcc = 1.75f;

	bool bKinimatic = false;

public:
	Boid(ofVec2f position, float orientation);

	void SetUp();
	void Update(float DeltaTime);
	void DrawBoid();

	pRigibody GetRidid();

	void SetKinematicInput(KinematicOutput input);
	void SetDynamicInput(DynamicOutput input);

	void CheckBoundary();
};
