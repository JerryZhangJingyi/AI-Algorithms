#pragma once

#include "Heuristic.h"
#include "ofMain.h"

class ManhattanDistance : public Heuristic
{
	float manhattanDistanceValue;
	float tileSize;
	int** worldSpace;
	int numberOfRows;
	int numberOfCols;

public:
	ManhattanDistance(float guessValue, float tileSize, int** worldSpace, int numberOfRows, int numberOfCols);
	float estimate(int givenNode, int targetNode);
};