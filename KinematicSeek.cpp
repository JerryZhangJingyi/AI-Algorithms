#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(rigibody* character, rigibody* target, float maxSpeed)
{
	this->Character = character;
	this->Target = target;
	this->MaxSpeed = maxSpeed;
}

kinematicOutput KinematicSeek::getKinematicSteering()
{
	KinematicOutput output = {ofVec2f::zero(), 0.0f};

	output.velocity = (Target->position - Character->position);
	//output.velocity = Character->position - Target->position;
	output.velocity.normalize();
	output.velocity *= MaxSpeed;
	/*
	if (abs(Character->position.x - Target->position.x) <= 1.0f && abs(Character->position.y - Target->position.y) <= 1.0f) {
		if (ConorIndex >= 3)
		{
			ConorIndex = 0;
		}
		else
		{
			ConorIndex++;
		}	

		Target->position = ConorPositions[ConorIndex];
	}
	*/
	if (output.velocity != ofVec2f::zero()) {
		Character->orientation = atan2(output.velocity.y, output.velocity.x);
	}

	output.rotation = 0.0f;

	return output;
}
