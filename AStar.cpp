#include "AStar.h"
#include <chrono>


AStar::AStar(DirectedWrightedGraph* graph, Heuristic* heuristic)
{
	this->graph = graph;
	//this->fringe = new std::priority_queue<nodeRecord>(); // open list
	//this->visitedNodes = new std::vector<nodeRecord>(); // close list
	this->open = new std::list<nodeRecord>();
	this->close = new std::list<nodeRecord>();
	this->heuristic = heuristic;
}

AStar::~AStar()
{
	//this->fringe->~priority_queue();
	//this->visitedNodes->~vector();

	//delete this->fringe;
	//delete this->visitedNodes;

	delete this->open;
	delete this->close;
}

std::vector<directedWeightedEdge*>* AStar::findPath(int sourceNode, int sinkNode)
{
	// set clock
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	auto t1 = high_resolution_clock::now();

	//inti fringe
	float heuristicEstimateFromStart = this->heuristic->estimate(sourceNode, sinkNode);

	std::cout << "Estimation: " << heuristicEstimateFromStart << std::endl;

	nodeRecord startNodeRecord = { sourceNode, NULL, 0.0f, heuristicEstimateFromStart };

	//this->fringe->push(startNodeRecord);
	this->open->push_back(startNodeRecord);

	//fringe not empty
	nodeRecord element = {};

	//while (!this->fringe->empty())
	while(this->open->size() != 0)
	{
		//element = this->fringe->top();
		this->open->sort();
		element = this->open->front();

		//this->fringe->pop();

		if (element.node == sinkNode)
		{
			break;
		}
		std::vector<pDirectedWeightedEdge> *outgoingEdges = this->graph->getOutGoingEdges(element.node);

		for (pDirectedWeightedEdge& outgoingEdge : *outgoingEdges)
		{
			int sink = outgoingEdge->sinkNode;

			float costToAdd = outgoingEdge->edgeCost;
			float newCostSoFar = element.costSoFar + costToAdd;

			float heuristicFromChild = this->heuristic->estimate(sink, sinkNode);
			float etcForChild = newCostSoFar + heuristicFromChild;

			nodeRecord childRecord = { sink, outgoingEdge, newCostSoFar, etcForChild };
			/*
			auto it = find(this->visitedNodes->begin(), this->visitedNodes->end(), childRecord);
			if (it != this->visitedNodes->end())
			{
				nodeRecord oldChildRecord = *it;

				if (childRecord.costSoFar < oldChildRecord.costSoFar)
				{
					this->visitedNodes->erase(it);
				}
				else
				{
					continue;
				}
			}
			this->fringe->push(childRecord);
			*/
			/*
			bool foundClosed = false;
			for (int i = 0; i < this->visitedNodes->size(); i++)
			{
				if (childRecord.node == this->visitedNodes->at(i).node)
				{
					foundClosed = true;

					nodeRecord oldChildRecord = this->visitedNodes->at(i);

					if (childRecord.costSoFar < oldChildRecord.costSoFar)
					{
						this->visitedNodes->erase(this->visitedNodes->begin() + i);
					}
					else
					{
						continue;
					}
					
				}
			}
			if (foundClosed == false)
			{
				this->fringe->push(childRecord);
			}
			*/

			float endNodeHeuristic = 0;
			nodeRecord oldChildRecord = {};
			if (std::find(this->close->begin(), this->close->end(), childRecord) != this->close->end())
			{
				oldChildRecord = *std::find(this->close->begin(), this->close->end(), childRecord);

				if (oldChildRecord.costSoFar <= childRecord.costSoFar)
				{
					continue;
				}
				this->close->remove(oldChildRecord);

				endNodeHeuristic = oldChildRecord.estimatedTotalCost - oldChildRecord.costSoFar;
			}
			else if(std::find(this->open->begin(), this->open->end(), childRecord) != this->open->end())
			{
				oldChildRecord = *std::find(this->open->begin(), this->open->end(), childRecord);

				if (oldChildRecord.costSoFar <= childRecord.costSoFar)
				{
					continue;
				}

				endNodeHeuristic = oldChildRecord.estimatedTotalCost - oldChildRecord.costSoFar;
			}
			else
			{
				oldChildRecord = childRecord;
			}

			if (std::find(this->open->begin(), this->open->end(), oldChildRecord) != this->open->end() == false)
			{
				open->push_back(oldChildRecord);
			}

		}
		this->open->remove(element);
		this->close->push_back(element);
		//this->visitedNodes->push_back(element);
		
	}

	//if didnt find goal
	
	if (element.node != sinkNode)
	{
		//this->fringe = new std::priority_queue<nodeRecord>();
		//this->visitedNodes = new std::vector<nodeRecord>();
		this->open = new std::list<nodeRecord>();
		this->close = new std::list<nodeRecord>();
		return NULL;
	}
	
	//assemble path to goal
	std::vector<pDirectedWeightedEdge>* path = new std::vector<pDirectedWeightedEdge>();
	while (element.node != sourceNode)
	{
		path->insert(path->begin(), element.incomingEdge);
		nodeRecord parent = {element.incomingEdge->sourceNode, NULL, 0.0f, 0.0f};

		/*
		auto it = find(this->visitedNodes->begin(), this->visitedNodes->end(), parent);
		if (it != this->visitedNodes->end())
		{
			element = *it;
		}
		*/

		auto it = find(this->close->begin(), this->close->end(), parent);
		if (it != this->close->end())
		{
			element = *it;
		}
	}
	/*
	for (int i = 0; i < path->size(); i++)
	{
		std::cout << path->size() << std::endl;
	}
	*/

	//this->fringe = new std::priority_queue<nodeRecord>();
	//this->visitedNodes = new std::vector<nodeRecord>();
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
