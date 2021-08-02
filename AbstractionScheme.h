#pragma once

#include "ofMain.h"
#include "DirectedGraph.h"

class AbstractionScheme
{
public:
	virtual int quantization(ofVec2f position) = 0;

	virtual ofVec2f localization(int node) = 0;

	virtual DirectedWrightedGraph* getGraphSpace() = 0;

};