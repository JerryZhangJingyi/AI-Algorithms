#pragma once

#include <stdio.h>
#include "Types.h"

class DynamicSeek {
public:
	rigibody* Character;
	rigibody* Target;
	float MaxAcc;

	DynamicSeek(rigibody* character, rigibody* target, float maxAcc);

	dynamicOutput getDynamicSteering();
};