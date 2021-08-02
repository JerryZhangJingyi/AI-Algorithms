#include "DynamicArrive.h"

DynamicArrive::DynamicArrive(rigibody* character, rigibody* target, float maxAcc, float maxSpeed, float slowRadius, float targetRadius, float timeToTargetVelocity)
{
	this->Character = character;
	this->Target = target;
	this->MaxAcc = maxAcc;
	this->MaxSpeed = maxSpeed;
	this->SlowRadius = slowRadius;
	this->TargetRadius = targetRadius;
	this->TimeToTargetVelocity = timeToTargetVelocity;
}

dynamicOutput DynamicArrive::getDynamicSteering()
{
	dynamicOutput steering = { ofVec2f::zero(), 0.0f };

	ofVec2f direction = Target->position - Character->position;
	float distance = direction.length();

	float targetSpeed = 0.0f;


	if (distance < TargetRadius)
	{
		//return steering;
		return { -ofVec2f::zero(), 0.0f };
	}

	if (distance > SlowRadius)
	{
		targetSpeed = MaxSpeed;
	}
	else
	{
		targetSpeed = MaxSpeed * (distance / SlowRadius);
	}

	direction.normalize();
	ofVec2f desiredVelocity = (direction) * targetSpeed;

	steering.linear = (desiredVelocity - Character->velocity) / TimeToTargetVelocity;

	if (steering.linear.length() > MaxAcc)
	{
		steering.linear.normalize();
		steering.linear *= MaxAcc;
	}

	//Character->orientation = atan2(desiredVelocity.y, desiredVelocity.x);

	steering.angular = 0.0f;

	return steering;
}
