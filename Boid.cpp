
#include "Boid.h"

Boid::Boid(ofVec2f position, float orientation) {

	rigid.position = position;
	rigid.orientation = orientation;

	rigid.velocity = ofVec2f::zero();
	rigid.rotation = 0;

	kinematicInput = { ofVec2f::zero(), 0.0f };
	dynamicInput = { ofVec2f::zero(), 0.0f };
}

void Boid::DrawBoid() {
	ofPushMatrix();

	ofTranslate(rigid.position.x, rigid.position.y);
	ofRotateRad(rigid.orientation);
	ofSetColor(ofColor(255, 0, 0));
	/*
	float y_top = rigid.position.y - (width / 2) + width;
	float y_bottom = rigid.position.y + (width / 2) + width;
	float x_nose = rigid.position.x + 2 * width + width;
	*/
	//ofSetColor(0xFF000000);

	//ofDrawCircle(rigid.position.x + (width), rigid.position.y + (width), width);
	ofDrawCircle(0, 0, radius);

	float x1 = 0;
	float x2 = 0;
	float x3 = width;
	float y1 = -radius;
	float y2 = radius;
	float y3 = 0;

	//ofDrawTriangle(rigid.position.x + (width / 2), y_top, rigid.position.x + (width / 2), y_bottom, x_nose, rigid.position.y + width);
	ofDrawTriangle(x1, y1, x2, y2, x3, y3);

	ofPopMatrix();
}

rigibody* Boid::GetRidid()
{
	return &rigid;
}

void Boid::SetKinematicInput(KinematicOutput input)
{
	this->kinematicInput = input;
}

void Boid::SetDynamicInput(DynamicOutput input)
{
	this->dynamicInput = input;
}

void Boid::CheckBoundary()
{
	if (this->rigid.position.x < minWidth)
	{
		this->rigid.position.x = maxWidth - 1;
		return;
	}
	else if (this->rigid.position.x > maxWidth)
	{
		this->rigid.position.x = minWidth + 1;
		return;
	}
	else if (this->rigid.position.y < minHeight)
	{
		this->rigid.position.y = maxHeight - 1;
		return;
	}
	else if (this->rigid.position.y > maxHeight)
	{
		this->rigid.position.y = minHeight + 1;
		return;
	}
}

void Boid::Update(float DeltaTime) {
	if (bKinimatic == true)
	{
		if (this->kinematicInput.velocity != ofVec2f::zero() || this->kinematicInput.rotation > 0 || this->kinematicInput.rotation < 0) {
			this->rigid.position += kinematicInput.velocity * DeltaTime * 3;
			this->rigid.orientation += kinematicInput.rotation * DeltaTime;
		}
	}
	else
	{
		/*
		if (this->dynamicInput.linear != ofVec2f::zero() || this->dynamicInput.angular > 0 || this->dynamicInput.angular < 0) {
			this->rigid.position += this->rigid.velocity * DeltaTime;
			this->rigid.orientation += this->rigid.rotation * DeltaTime;

			this->rigid.velocity += dynamicInput.linear * DeltaTime;
			this->rigid.rotation += dynamicInput.angular * DeltaTime;

			if (this->rigid.velocity.length() > this->maxSpeed) {
				this->rigid.velocity.normalize();
				this->rigid.velocity *= this->maxSpeed;
			}
		}
		*/

		this->rigid.position += this->rigid.velocity * DeltaTime;
		this->rigid.orientation += this->rigid.rotation * DeltaTime;

		this->rigid.velocity += dynamicInput.linear * DeltaTime;
		this->rigid.rotation += dynamicInput.angular * DeltaTime;

		if (this->rigid.velocity.length() > this->maxSpeed) {
			this->rigid.velocity.normalize();
			this->rigid.velocity *= this->maxSpeed;
		}

		if (glm::abs(this->rigid.rotation) > this->maxRotation)
		{
			float sign = (this->rigid.rotation) / glm::abs(this->rigid.rotation);
			this->rigid.rotation = this->maxRotation * sign;
		}

		CheckBoundary();
	}
	
	/*
	
	if (this->dynamicInput.linear != ofVec2f::zero() || this->dynamicInput.angular > 0 || this->dynamicInput.angular < 0) {
		this->rigid.position += this->rigid.velocity * DeltaTime;
		this->rigid.orientation += this->rigid.rotation * DeltaTime;

		this->rigid.velocity += dynamicInput.linear * DeltaTime;
		this->rigid.rotation += dynamicInput.angular * DeltaTime;

		if (this->rigid.velocity.length() > this->maxSpeed) {
			this->rigid.velocity.normalize();
			this->rigid.velocity *= this->maxSpeed;
		}
	}
	
	
	this->rigid.position += this->rigid.velocity * DeltaTime;
	this->rigid.orientation += this->rigid.rotation * DeltaTime;

	this->rigid.velocity += dynamicInput.linear * DeltaTime;
	this->rigid.rotation += dynamicInput.angular * DeltaTime;

	if (this->rigid.velocity.length() > this->maxSpeed) {
		this->rigid.velocity.normalize();
		this->rigid.velocity *= this->maxSpeed;
	}
	
	if (glm::abs(this->rigid.rotation) > this->maxRotation)
	{
		float sign = (this->rigid.rotation) / glm::abs(this->rigid.rotation);
		this->rigid.rotation = this->maxRotation * sign;
	}

	CheckBoundary();
	*/
}