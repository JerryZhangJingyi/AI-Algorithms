#pragma once

class Heuristic {
public:
	virtual float estimate(int givenNode, int targetNode) = 0;
};