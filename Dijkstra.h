#pragma once
#include "AStar.h"
#include "PathFinder.h"

class Dijkstra : public PathFinder
{
	DirectedWrightedGraph* graph;
	std::list<nodeRecord>* open;
	std::list<nodeRecord>* close;

public:
	Dijkstra(DirectedWrightedGraph* graph);
	~Dijkstra();
	std::vector<directedWeightedEdge*>* findPath(int sourceNode, int sinkNode);
};