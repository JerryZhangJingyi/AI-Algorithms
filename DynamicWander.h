#pragma once


#include <stdio.h>
#include "Types.h"

class DynamicWander {
public:
	rigibody* Character;
	rigibody* Target;
	float MaxAngularAcc;
	float MaxAngularSpeed;
	float SlowAngle;
	float TargetAngle;
	float TimeToTargetRotation;
	float MaxSpeed;

	DynamicWander(rigibody* character, rigibody* target, float maxAngularAcc, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToTargetRotation, float maxSpeed);

	dynamicOutput getDynamicSteering();

	float RandomBinomial();
};