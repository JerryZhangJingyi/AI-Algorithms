#include "DynamicAlign.h"

DynamicAlign::DynamicAlign(rigibody* character, rigibody* target, float maxAngularAcc, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToTargetRotation)
{
	this->Character = character;
	this->Target = target;
	this->MaxAngularAcc = maxAngularAcc;
	this->MaxAngularSpeed = maxAngularSpeed;
	this->SlowAngle = slowAngle;
	this->TargetAngle = targetAngle;
	this->TimeToTargetRotation = timeToTargetRotation;
}

dynamicOutput DynamicAlign::getDynamicSteering()
{
	dynamicOutput steering = { ofVec2f::zero(), 0.0f };

	float orientationChange = Character->orientation - Target->orientation;
	float smallestChange = MapToPiRange(orientationChange);

	float angularDistance = glm::abs(smallestChange);
	float targetRotation = 0.0f;

	if (angularDistance < TargetAngle)
	{
		return steering;
	}
	else if (angularDistance > SlowAngle)
	{
		targetRotation = MaxAngularSpeed;
	}
	else
	{
		targetRotation = MaxAngularSpeed * (angularDistance / SlowAngle);
	}

	float accSign = smallestChange / angularDistance;
	targetRotation *= (smallestChange / angularDistance);

	steering.angular = (targetRotation - Character->rotation) / TimeToTargetRotation;

	if (glm::abs(steering.angular) > MaxAngularAcc) 
	{
		steering.angular = MaxAngularAcc * accSign;
	}

	//steering.linear = ofVec2f::zero();

	return steering;
}

float DynamicAlign::MapToPiRange(float angleInRadians)
{
	float mappedValue = angleInRadians;

	while (mappedValue > glm::pi<float>())
	{
		mappedValue -= glm::two_pi<float>();
	}

	while (mappedValue < -glm::pi<float>())
	{
		mappedValue += glm::two_pi<float>();
	}

	return mappedValue;
}
