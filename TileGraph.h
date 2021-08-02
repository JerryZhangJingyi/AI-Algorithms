#pragma once

#include "AbstractionScheme.h"
#include "DirectedGraph.h"

class TileGraph : public AbstractionScheme {

	const float GRAPH_EDGE_COST = 1.0f;

	int nodeIdCounter;

public:
	int** worldSpace;

	float tileSize;

	int numberOfRows;
	int numberOfCols;

	static const int TILE_BLOCKED = -1;
	DirectedWrightedGraph* graphSpace;

	TileGraph(int numberOfRows, int numberOfCols, float tileSize);
	~TileGraph();
	int quantization(ofVec2f position);

	ofVec2f localization(int node);

	DirectedWrightedGraph* getGraphSpace();

	int getRows();
	int getCols();
	float getTileSize();
	int getTileValue(int row, int col);
	int setTileValue(int row, int col);
};