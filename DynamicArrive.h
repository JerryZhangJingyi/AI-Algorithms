#pragma once

#include <stdio.h>
#include "Types.h"

class DynamicArrive {
public:
	rigibody* Character;
	rigibody* Target;
	float MaxAcc;
	float MaxSpeed;
	float SlowRadius;
	float TargetRadius;
	float TimeToTargetVelocity;

	DynamicArrive(rigibody* character, rigibody* target, float maxAcc, float maxSpeed, float slowRadius, float targetRadius, float timeToTargetVelocity);

	dynamicOutput getDynamicSteering();
};