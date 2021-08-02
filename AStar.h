#pragma once

#include <queue>
#include <vector>
#include <list>
#include "PathFinder.h"
#include "Heuristic.h"

typedef struct nodeRecord
{
	int node; //current node
	pDirectedWeightedEdge incomingEdge;
	float costSoFar;
	float estimatedTotalCost;
} nodeRecord, * pNodeRecord;

inline bool operator < (const nodeRecord& left, const nodeRecord& right)
{
	return left.estimatedTotalCost < right.estimatedTotalCost;
}

inline bool operator > (const nodeRecord& left, const nodeRecord& right)
{
	return left.estimatedTotalCost > right.estimatedTotalCost;
}

inline bool operator == (const nodeRecord& left, const nodeRecord& right)
{
	return !(left < right) && !(right > left) && (left.node == right.node);
}

class AStar : public PathFinder
{
	DirectedWrightedGraph* graph;
	//std::priority_queue<nodeRecord>* fringe;
	//std::vector<nodeRecord>* visitedNodes;
	std::list<nodeRecord>* open;
	std::list<nodeRecord>* close;
	Heuristic* heuristic;

public:
	AStar(DirectedWrightedGraph* graph, Heuristic* heuristic);
	~AStar();
	std::vector<directedWeightedEdge*>* findPath(int sourceNode, int sinkNode);
};