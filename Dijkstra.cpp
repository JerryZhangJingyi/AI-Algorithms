#include "Dijkstra.h"
#include <chrono>

Dijkstra::Dijkstra(DirectedWrightedGraph* graph)
{
	this->graph = graph;
	this->open = new std::list<nodeRecord>();
	this->close = new std::list<nodeRecord>();
}

Dijkstra::~Dijkstra()
{
	delete this->open;
	delete this->close;
}

std::vector<directedWeightedEdge*>* Dijkstra::findPath(int sourceNode, int sinkNode)
{
	// set clock
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	auto t1 = high_resolution_clock::now();

	//inti fringe
	//float heuristicEstimateFromStart = this->heuristic->estimate(sourceNode, sinkNode);

	//std::cout << "Estimation: " << heuristicEstimateFromStart << std::endl;

	nodeRecord startNodeRecord = { sourceNode, NULL, 0.0f, 0.0f };

	//this->fringe->push(startNodeRecord);
	this->open->push_back(startNodeRecord);

	//fringe not empty
	nodeRecord element = {};

	while (this->open->size() != 0)
	{
		this->open->sort();
		element = this->open->front();


		if (element.node == sinkNode)
		{
			break;
		}
		std::vector<pDirectedWeightedEdge>* outgoingEdges = this->graph->getOutGoingEdges(element.node);

		for (pDirectedWeightedEdge& outgoingEdge : *outgoingEdges)
		{
			int sink = outgoingEdge->sinkNode;

			float costToAdd = outgoingEdge->edgeCost;
			float newCostSoFar = element.costSoFar + costToAdd;

			//float heuristicFromChild = this->heuristic->estimate(sink, sinkNode);
			float etcForChild = newCostSoFar;

			nodeRecord childRecord = { sink, outgoingEdge, newCostSoFar, etcForChild };

			nodeRecord oldChildRecord = {};
			if (std::find(this->close->begin(), this->close->end(), childRecord) != this->close->end())
			{
				oldChildRecord = *std::find(this->close->begin(), this->close->end(), childRecord);

				if (oldChildRecord.costSoFar <= childRecord.costSoFar)
				{
					continue;
				}
				this->close->remove(oldChildRecord);
			}
			else if (std::find(this->open->begin(), this->open->end(), childRecord) != this->open->end())
			{
				oldChildRecord = *std::find(this->open->begin(), this->open->end(), childRecord);

				if (oldChildRecord.costSoFar <= childRecord.costSoFar)
				{
					continue;
				}
			}
			else
			{
				oldChildRecord = { sink, outgoingEdge, newCostSoFar, etcForChild };
			}

			if (std::find(this->open->begin(), this->open->end(), oldChildRecord) != this->open->end() == false)
			{
				open->push_back(oldChildRecord);
			}

		}
		this->open->remove(element);
		this->close->push_back(element);

	}


	if (element.node != sinkNode)
	{
		this->open = new std::list<nodeRecord>();
		this->close = new std::list<nodeRecord>();
		return NULL;
	}

	std::vector<pDirectedWeightedEdge>* path = new std::vector<pDirectedWeightedEdge>();
	while (element.node != sourceNode)
	{
		path->insert(path->begin(), element.incomingEdge);
		nodeRecord parent = { element.incomingEdge->sourceNode, NULL, 0.0f, 0.0f };

		auto it = find(this->close->begin(), this->close->end(), parent);
		if (it != this->close->end())
		{
			element = *it;
		}
	}

	this->open = new std::list<nodeRecord>();
	this->close = new std::list<nodeRecord>();

	//set clock
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << ms_double.count() << "ms" << std::endl;
	std::cout << "Path Length: " << path->size() << std::endl;
	std::cout << std::endl;
	return path;
}
