#pragma once
#include "DirectedGraph.h"


class PathFinder {
public:
	virtual std::vector<directedWeightedEdge*>* findPath(int sourceNode, int sinkNode) = 0;
};