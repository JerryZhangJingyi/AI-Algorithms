#pragma once
#include "ofMain.h"
class Block
{
private:
	float width = 16.0f;
	float height = 16.0f;


public:
	Block(ofVec2f position, float orientation);

	void SetUp();
	void Update(float DeltaTime);
	void DrawBlock();
};