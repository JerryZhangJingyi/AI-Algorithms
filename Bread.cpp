#include "Bread.h"

void Bread::DrawBread()
{
	ofPushMatrix();

	ofTranslate(position.x, position.y);

	ofSetColor(ofColor(255, 0, 0));
	ofDrawCircle(0, 0, radius);

	ofPopMatrix();
}
