#pragma once

#include "Heuristic.h"
#include "ofMain.h"

class EuclideanDistance : public Heuristic
{
	float euclideanDistanceValue;
	float tileSize;
	int** worldSpace;
	int numberOfRows;
	int numberOfCols;

public:
	EuclideanDistance(float guessValue, float tileSize, int** worldSpace, int numberOfRows, int numberOfCols);
	float estimate(int givenNode, int targetNode);
};