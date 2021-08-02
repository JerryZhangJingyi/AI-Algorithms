#pragma once
#include "Heuristic.h"

class ConstantGuessHeuristic : public Heuristic
{
	float constantGuessValue;

public:
	ConstantGuessHeuristic(float guessValue);
	float estimate(int givenNode, int targetNode);
};