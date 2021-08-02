#pragma once

#include "ofMain.h"
#include "../Boid.h"
#include "../Bread.h"
#include "../KinematicSeek.h"
#include "../DynamicSeek.h"
#include "../DynamicArrive.h"
#include "../DynamicAlign.h"
#include "../DynamicWander.h"
#include "../GameLevel.h"
#include "../AStar.h"
#include "../ConstantGuess.h"
#include "../ManhattanDistance.h"
#include "../EuclideanDistance.h"
#include "../Dijkstra.h"

class ofApp : public ofBaseApp{

	Boid* boid = NULL;
	Boid* target = NULL;
	Boid* finalTarget = NULL;
	KinematicSeek* kinematicSeek = NULL;
	DynamicSeek* dynamicSeek = NULL;
	DynamicArrive* dynamicArrive = NULL;
	DynamicAlign* dynamicAlign = NULL;
	DynamicWander* dynamicWander = NULL;

	GameLevel* level = NULL;

	ConstantGuessHeuristic* guess = NULL;
	ManhattanDistance* manhattanDistance = NULL;
	EuclideanDistance* euclideanDistance = NULL;
	Dijkstra* dijkstra = NULL;

	AStar* AStarSearch = NULL;

	Bread* breads = new Bread[100];
	int breadIndex = 0;
	float breadDelay = 0.2f;
	float breadTimer = breadDelay;

	std::vector<pDirectedWeightedEdge>* path;
	int pathIndex = 0;
	bool bTreeTargetSet = false;

public:
	enum TreeNodes { node1 = 1, node2 = 2, node3 = 3 };
	int Treenode = 1;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
	void RandomTargetPosition();
	float RandomBinomial();
		
};
