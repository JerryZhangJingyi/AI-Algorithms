#include "DynamicSeek.h"

DynamicSeek::DynamicSeek(rigibody* character, rigibody* target, float maxAcc)
{
	this->Character = character;
	this->Target = target;
	this->MaxAcc = maxAcc;
}

DynamicOutput DynamicSeek::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };

	output.linear = Target->position - Character->position;

	float distance = (Target->position - Character->position).length();

	if (distance < 12.0f)
	{
		if (Character->velocity != ofVec2f::zero())
		{
			Character->velocity = ofVec2f::zero();
		}
		//return steering;
		return { -ofVec2f::zero(), 0.0f };
	}

	output.linear.normalize();
	output.linear *= MaxAcc;
	Character->orientation = atan2(output.linear.y, output.linear.x);

	return output;
}
