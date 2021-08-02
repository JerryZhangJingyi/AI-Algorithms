#include "TileGraph.h"

TileGraph::TileGraph(int numberOfRows, int numberOfCols, float tileSize)
{
	this->nodeIdCounter = 0;
	this->numberOfRows = numberOfRows;
	this->numberOfCols = numberOfCols;
	this->tileSize = tileSize;

	this->worldSpace = new int*[this->numberOfRows];

	for (int row = 0; row < this->numberOfRows; ++row)
	{
		this->worldSpace[row] = new int[this->numberOfCols];

		for (int col = 0; col < this->numberOfCols; ++col)
		{
			this->worldSpace[row][col] = TILE_BLOCKED;
		}
	}

	this->graphSpace = new DirectedWrightedGraph();
}

TileGraph::~TileGraph()
{
	for (int row = 0; row < this->numberOfRows; ++row)
	{
		delete[] this->worldSpace[row];
	}
	delete[] this->worldSpace;
	delete this->graphSpace;
}

int TileGraph::quantization(ofVec2f position)
{
	int row = (int)(position.y / tileSize);
	int col = (int)(position.x / tileSize);
	return worldSpace[row][col];
}

ofVec2f TileGraph::localization(int node)
{
	ofVec2f locolizedPosition = ofVec2f(-1, -1);

	int col = -1;
	int row = -1;
	for (int i = 0; i < this->numberOfRows; ++i)
	{
		for (int j = 0; j < this->numberOfCols; ++j)
		{
			if (this->worldSpace[i][j] == node)
			{
				row = i;
				col = j;
				goto outsidedoublefor;
			}
		}
	}

	outsidedoublefor:

	locolizedPosition.x = (col * this->tileSize) + (this->tileSize / 2.0f);
	locolizedPosition.y = (row * this->tileSize) + (this->tileSize / 2.0f);
	/*
	if (col == this->numberOfCols || row == this->numberOfRows)
	{
		return { -1, -1 };
	}
	else
	{
		locolizedPosition.x = (col * this->tileSize) + (this->tileSize / 2.0f);
		locolizedPosition.y = (row * this->tileSize) + (this->tileSize / 2.0f);
	}
	*/
	return locolizedPosition;
}

DirectedWrightedGraph* TileGraph::getGraphSpace()
{
	return this->graphSpace;
}

int TileGraph::getRows()
{
	return this->numberOfRows;
}

int TileGraph::getCols()
{
	return this->numberOfCols;
}

float TileGraph::getTileSize()
{
	return this->tileSize;
}

int TileGraph::getTileValue(int row, int col)
{
	if (row < 0 || row > this->numberOfRows)
	{
		return TILE_BLOCKED;
	}

	if (col < 0 || col > this->numberOfCols)
	{
		return TILE_BLOCKED;
	}

	return this->worldSpace[row][col];
}

int TileGraph::setTileValue(int row, int col)
{
	if (row < 0 || row >= numberOfRows)
	{
		return TILE_BLOCKED;
	}

	if (col < 0 || col >= numberOfCols)
	{
		return TILE_BLOCKED;
	}

	int newNodeId = nodeIdCounter;
	this->nodeIdCounter++;
	this->worldSpace[row][col] = newNodeId;

	if (col != this->numberOfCols - 1)
	{
		int rightNeighborCol = col + 1;
		int neighborNodeID = this->worldSpace[row][rightNeighborCol];

		if (neighborNodeID != TILE_BLOCKED)
		{
			this->graphSpace->addDirectedWeightedEdge(newNodeId, neighborNodeID, GRAPH_EDGE_COST);
			this->graphSpace->addDirectedWeightedEdge(neighborNodeID, newNodeId, GRAPH_EDGE_COST);
		}
	}

	if (row != this->numberOfRows - 1)
	{
		int downNeighborRow = row + 1;
		int neighborNodeID = this->worldSpace[downNeighborRow][col];

		if (neighborNodeID != TILE_BLOCKED)
		{
			this->graphSpace->addDirectedWeightedEdge(newNodeId, neighborNodeID, GRAPH_EDGE_COST);
			this->graphSpace->addDirectedWeightedEdge(neighborNodeID, newNodeId, GRAPH_EDGE_COST);
		}
	}

	if (col > 0)
	{
		int leftNeighborCol = col - 1;
		int neighborNodeID = this->worldSpace[row][leftNeighborCol];

		if (neighborNodeID != TILE_BLOCKED)
		{
			this->graphSpace->addDirectedWeightedEdge(newNodeId, neighborNodeID, GRAPH_EDGE_COST);
			this->graphSpace->addDirectedWeightedEdge(neighborNodeID, newNodeId, GRAPH_EDGE_COST);
		}
	}

	if (row > 0)
	{
		int upNeighborRow = row - 1;
		int neighborNodeID = this->worldSpace[upNeighborRow][col];

		if (neighborNodeID != TILE_BLOCKED)
		{
			this->graphSpace->addDirectedWeightedEdge(newNodeId, neighborNodeID, GRAPH_EDGE_COST);
			this->graphSpace->addDirectedWeightedEdge(neighborNodeID, newNodeId, GRAPH_EDGE_COST);
		}
	}

	return newNodeId;
}
