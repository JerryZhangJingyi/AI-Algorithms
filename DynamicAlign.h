#pragma once

#include <stdio.h>
#include "Types.h"

class DynamicAlign {
public:
	rigibody* Character;
	rigibody* Target;
	float MaxAngularAcc;
	float MaxAngularSpeed;
	float SlowAngle;
	float TargetAngle;
	float TimeToTargetRotation;

	DynamicAlign(rigibody* character, rigibody* target, float maxAngularAcc, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToTargetRotation);

	dynamicOutput getDynamicSteering();

	float MapToPiRange(float angleInRadians);
};