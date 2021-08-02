#include "DynamicWander.h"

DynamicWander::DynamicWander(rigibody* character, rigibody* target, float maxAngularAcc, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToTargetRotation, float maxSpeed)
{
	this->Character = character;
	this->Target = target;
	this->MaxAngularAcc = maxAngularAcc;
	this->MaxAngularSpeed = maxAngularSpeed;
	this->SlowAngle = slowAngle;
	this->TargetAngle = targetAngle;
	this->TimeToTargetRotation = timeToTargetRotation;
	this->MaxSpeed = maxSpeed;
}

dynamicOutput DynamicWander::getDynamicSteering()
{
	if (Character->orientation > 6.28319f)
	{
		Character->orientation = 0.f;
	}
	else if (Character->orientation < 0.f)
	{
		Character->orientation = 6.28319f;
	}

	dynamicOutput steering = { ofVec2f::zero(), 0.0f };

	float orientationOffset = 40.0f * RandomBinomial();

	float OrientationTarget = Character->orientation + orientationOffset;

	steering.angular = (OrientationTarget - Character->rotation) / TimeToTargetRotation;

	ofVec2f direction = 0.0f - Character->position;
	ofVec2f desiredVelocity = (direction)*MaxSpeed;

	//std::cout << std::fixed << std::setprecision(2) << Character->orientation;

	if (Character->orientation < 1.5708f) // 0 - 90 degrees
	{
		Character->velocity.y = sinf(Character->orientation) * MaxSpeed;
		Character->velocity.x = cosf(Character->orientation) * MaxSpeed;

	}
	else if (Character->orientation < 3.14159f) // 90 - 180 degrees
	{
		Character->velocity.x = -sinf(Character->orientation - 1.5708f) * MaxSpeed;
		Character->velocity.y = cosf(Character->orientation - 1.5708f) * MaxSpeed;

	}
	else if (Character->orientation < 4.71239f) // 180 - 270 degrees
	{
		Character->velocity.y = -sinf(Character->orientation - 3.14159f) * MaxSpeed;
		Character->velocity.x = -cosf(Character->orientation - 3.14159f) * MaxSpeed;

	}
	else if (Character->orientation < 6.28319f) // 270 - 360 degrees
	{
		Character->velocity.x = sin(Character->orientation - 4.71239f) * MaxSpeed;
		Character->velocity.y = -cosf(Character->orientation - 4.71239f) * MaxSpeed;

	}
	
	steering.linear = Character->velocity;

	return steering;
}

float DynamicWander::RandomBinomial()
{
	return ofRandom(0.0f, 1.0f) - ofRandom(0.0f, 1.0f);
}