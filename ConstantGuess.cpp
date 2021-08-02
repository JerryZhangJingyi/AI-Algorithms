#include "ConstantGuess.h"

ConstantGuessHeuristic::ConstantGuessHeuristic(float guessValue)
{
	this->constantGuessValue = guessValue;
}

float ConstantGuessHeuristic::estimate(int givenNode, int targetNode)
{
	return constantGuessValue;
}
