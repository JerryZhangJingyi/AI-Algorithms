#pragma once

#include "ofMain.h"

typedef struct RigidBody {
	ofVec2f position;
	float orientation;

	ofVec2f velocity;
	float rotation;
} rigibody, *pRigibody;

typedef struct KinematicOutput {
	ofVec2f velocity;
	float rotation;
} kinematicOutput;

typedef struct DynamicOutput {
	ofVec2f linear;
	float angular;
} dynamicOutput;