#include "ManhattanDistance.h"

ManhattanDistance::ManhattanDistance(float guessValue, float tileSize, int** worldSpace, int numberOfRows, int numberOfCols)
{
	this->manhattanDistanceValue = guessValue;
	this->tileSize = tileSize;
	this->worldSpace = worldSpace;
	this->numberOfRows = numberOfRows;
	this->numberOfCols = numberOfCols;
}

float ManhattanDistance::estimate(int givenNode, int targetNode)
{
	ofVec2f givenPosition, targetPosition;

	int col = -1;
	int row = -1;
	for (int i = 0; i < this->numberOfRows; ++i)
	{
		for (int j = 0; j < this->numberOfCols; ++j)
		{
			if (this->worldSpace[i][j] == givenNode)
			{
				col = j;
				row = i;
				break;
			}
		}
	}

	givenPosition.x = (col * this->tileSize) + (this->tileSize / 2.0f);
	givenPosition.y = (row * this->tileSize) + (this->tileSize / 2.0f);

	col = -1;
	row = -1;
	for (int i = 0; i < this->numberOfRows; ++i)
	{
		for (int j = 0; j < this->numberOfCols; ++j)
		{
			if (this->worldSpace[i][j] == targetNode)
			{
				col = j;
				row = i;
				break;
			}
		}
	}

	targetPosition.x = (col * this->tileSize) + (this->tileSize / 2.0f);
	targetPosition.y = (row * this->tileSize) + (this->tileSize / 2.0f);

	this->manhattanDistanceValue = (abs(givenPosition.x - targetPosition.x) + abs(givenPosition.y - targetPosition.y)) / this->tileSize;

	return this->manhattanDistanceValue;
}
