#include "DirectedGraph.h"

DirectedWrightedGraph::DirectedWrightedGraph()
{
	graph = std::map<int, std::vector<pDirectedWeightedEdge>*>();
}
/*
DirectedWrightedGraph::DirectedWrightedGraph(const std::filesystem::path& path)
{
	graph = std::map<int, std::vector<pDirectedWeightedEdge>>();
}
*/
DirectedWrightedGraph::~DirectedWrightedGraph()
{
	for (auto it = graph.begin(); it != graph.end(); ++it)
	{
		std::vector<pDirectedWeightedEdge>* value = (it->second);

		for (auto vecIt = value->begin(); vecIt != value->end(); ++vecIt)
		{
			pDirectedWeightedEdge edgePointer = *vecIt;
			delete edgePointer;
		}

		value->clear();
		delete value;
	}
}

std::vector<pDirectedWeightedEdge>* DirectedWrightedGraph::getOutGoingEdges(int sourceNode)
{
	auto it = graph.find(sourceNode);

	if (it != graph.end())
	{
		return graph[sourceNode];
	}
	else
	{
		std::vector<pDirectedWeightedEdge>* empty = new std::vector<pDirectedWeightedEdge>();
		graph[sourceNode] = empty;
		return empty;
	}
}

pDirectedWeightedEdge DirectedWrightedGraph::addDirectedWeightedEdge(int source, int sink, float edgeCost)
{
	std::vector<pDirectedWeightedEdge>* outgoingEdges = this->getOutGoingEdges(source);

	for (pDirectedWeightedEdge& edge : *outgoingEdges)
	{
		if(edge->sinkNode == sink)
		{
			return edge;
		}


	}

	pDirectedWeightedEdge newEdge = new directedWeightedEdge();
	newEdge->sourceNode = source;
	newEdge->sinkNode = sink;
	newEdge->edgeCost = edgeCost;

	outgoingEdges->push_back(newEdge);

	return newEdge;
}
