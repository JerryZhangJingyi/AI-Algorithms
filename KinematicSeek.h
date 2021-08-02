#pragma once
#include <stdio.h>
#include <iostream>
#include <list>
#include <../Types.h>
class KinematicSeek {

public:
	rigibody* Character;
	rigibody* Target;

	float MaxSpeed;

	KinematicSeek(rigibody* character, rigibody* target, float maxSpeed);

	kinematicOutput getKinematicSteering();

	float left_x = 50.0f;
	float right_x = 950.0f;
	float top_y = 50.0f;
	float bottom_y = 700.0f;

	int ConorIndex = 0;
	ofVec2f ConorPositions[4] = {
		{left_x, top_y}, 
		{right_x, top_y},
		{right_x, bottom_y},
		{left_x, bottom_y}
	};
};