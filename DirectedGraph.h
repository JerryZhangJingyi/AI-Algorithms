#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <filesystem>
#include "ofFileUtils.h"

typedef struct directedWeightedEdge
{
	int sourceNode;
	int sinkNode;
	float edgeCost;
} directedWeightedEdge, *pDirectedWeightedEdge;

class DirectedWrightedGraph
{
	std::map<int, std::vector<pDirectedWeightedEdge>*> graph;

public:
	DirectedWrightedGraph();
	//DirectedWrightedGraph(const std::filesystem::path& path);
	~DirectedWrightedGraph();
	std::vector<pDirectedWeightedEdge>* getOutGoingEdges(int sourceNode);
	pDirectedWeightedEdge addDirectedWeightedEdge(int source, int sink, float edgeCost);
};