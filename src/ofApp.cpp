#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(255, 255, 255);

	//ofVec2f start = {50.0f, 50.0f};
	ofVec2f boidStartCoordinate(256.0f, 224.0f);
	//ofVec2f boidStartCoordinate(0.0f, 0.0f);
	ofVec2f targetStartCoordination(10.f, 10.f);

	float init_orientation = 1.57f;
	float init_targetOrientation = 0.0f;

	boid = new Boid(boidStartCoordinate, init_orientation);
	target = new Boid(targetStartCoordination, init_targetOrientation);
	finalTarget = new Boid(targetStartCoordination, init_targetOrientation);

	kinematicSeek = new KinematicSeek(boid->GetRidid(), target->GetRidid(), 20.0f);
	dynamicSeek = new DynamicSeek(boid->GetRidid(), target->GetRidid(), boid->maxAcc);

	float slowRadius = 200.0f;
	float targetRadius = 80.0f;
	float timeToVelocityTarget = 0.005f;
	dynamicArrive = new DynamicArrive(boid->GetRidid(), target->GetRidid(), boid->maxAcc, boid->maxSpeed, slowRadius, targetRadius, timeToVelocityTarget);

	float slowAngle = glm::pi<float>() / 8;
	float targetAngle = glm::pi<float>() / 16;
	float timeToRotationTarget = 0.001f;
	dynamicAlign = new DynamicAlign(boid->GetRidid(), target->GetRidid(), boid->maxAngularAcc, boid->maxRotation, slowAngle, targetAngle, timeToRotationTarget);

	dynamicWander = new DynamicWander(boid->GetRidid(), target->GetRidid(), boid->maxAngularAcc, boid->maxRotation, slowAngle, targetAngle, timeToRotationTarget, 50.0f);

	level = new GameLevel("TestMap.level");

	// heuristics
	guess = new ConstantGuessHeuristic(0.0f);
	manhattanDistance = new ManhattanDistance(0.0f, level->levelTileGraph->tileSize, level->levelTileGraph->worldSpace, level->levelTileGraph->numberOfRows, level->levelTileGraph->numberOfCols);
	euclideanDistance = new EuclideanDistance(0.0f, level->levelTileGraph->tileSize, level->levelTileGraph->worldSpace, level->levelTileGraph->numberOfRows, level->levelTileGraph->numberOfCols);

	// searches
	//dijkstra = new Dijkstra(level->levelTileGraph->graphSpace);
	//AStarSearch = new AStar(level->levelTileGraph->graphSpace, guess);
	AStarSearch = new AStar(level->levelTileGraph->graphSpace, manhattanDistance);
	//AStarSearch = new AStar(level->levelTileGraph->graphSpace, euclideanDistance);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	float DeltaTime = ofGetLastFrameTime();
	int targetNode = 0;
	int currentNode = 0;
	float dist = 0;
	
	if (ofGetMousePressed())
	{
		//target->GetRidid()->position.x = ofGetMouseX();
		//target->GetRidid()->position.y = ofGetMouseY();
		if (ofGetMouseX() < 512 && ofGetMouseY() < 448 && ofGetMouseX() > 0 && ofGetMouseY() > 0)
		{
			targetNode = level->levelTileGraph->quantization(ofVec2f(ofGetMouseX(), ofGetMouseY()));
			currentNode = level->levelTileGraph->quantization(boid->GetRidid()->position);
			Treenode = 2;
			finalTarget->GetRidid()->position = ofVec2f(ofGetMouseX(), ofGetMouseY());

			path = AStarSearch->findPath(currentNode, targetNode);

			pathIndex = 0;

		}
		
	}
	
	if (boid != NULL)
	{
		switch (Treenode)
		{
		case node1:
			std::cout << "node1" << std::endl;

			boid->bKinimatic = false;
			boid->SetDynamicInput(dynamicWander->getDynamicSteering());
			boid->Update(DeltaTime);
			if (boid->GetRidid()->position.x >= 500 || boid->GetRidid()->position.x <= 10 || boid->GetRidid()->position.y >= 420 || boid->GetRidid()->position.y <= 10)
			{
				//Treenode = 2;
				//bTreeTargetSet = false;
			}
			
			break;

		case node2:
			std::cout << "node2" << std::endl;

			if (bTreeTargetSet == false)
			{
				//int randomX = 0 + (std::rand() % 512);
				//int randomY = 0 + (std::rand() % 448);

				//targetNode = level->levelTileGraph->quantization(ofVec2f(randomX, randomY));
				//currentNode = level->levelTileGraph->quantization(boid->GetRidid()->position);

				//finalTarget->GetRidid()->position = ofVec2f(randomX, randomY);

				//path = AStarSearch->findPath(currentNode, targetNode);

				//pathIndex = 0;

				boid->bKinimatic = true;

				bTreeTargetSet = true;
			}

			target->GetRidid()->position = level->levelTileGraph->localization(path->at(pathIndex)->sinkNode);

			boid->SetKinematicInput(kinematicSeek->getKinematicSteering());

			if (pathIndex < path->size() - 1)
			{
				boid->Update(DeltaTime);
			}

			dist = (boid->GetRidid()->position - target->GetRidid()->position).length();

			if (pathIndex < path->size() - 1 && dist <= 12.0f)
			{
				pathIndex++;
			}
			else if(pathIndex >= path->size() - 1)
			{
				Treenode = 3;
				pathIndex = 0;
				bTreeTargetSet = false;
				path = NULL;
			}

			break;

		case node3:
			std::cout << "node3" << std::endl;

			if (bTreeTargetSet == false)
			{
				targetNode = level->levelTileGraph->quantization(ofVec2f(512/2, 448/2));
				currentNode = level->levelTileGraph->quantization(boid->GetRidid()->position);

				finalTarget->GetRidid()->position = ofVec2f(512 / 2, 448 / 2);

				path = AStarSearch->findPath(currentNode, targetNode);

				pathIndex = 0;

				boid->bKinimatic = true;

				bTreeTargetSet = true;
			}

			target->GetRidid()->position = level->levelTileGraph->localization(path->at(pathIndex)->sinkNode);

			boid->SetKinematicInput(kinematicSeek->getKinematicSteering());

			if (pathIndex < path->size() - 1)
			{
				boid->Update(DeltaTime);
			}

			dist = (boid->GetRidid()->position - target->GetRidid()->position).length();

			if (pathIndex < path->size() - 1 && dist <= 12.0f)
			{
				pathIndex++;
			}
			else if (pathIndex >= path->size() - 1)
			{
				Treenode = 1;
				pathIndex = 0;
				bTreeTargetSet = false;
				path = NULL;
			}

			break;
		}

		//target->GetRidid()->position = level->levelTileGraph->localization(path->at(pathIndex)->sinkNode);

		//boid->SetKinematicInput(kinematicSeek->getKinematicSteering()); //basic-motion

		//boid->SetDynamicInput(dynamicSeek->getDynamicSteering());

		//boid->SetDynamicInput(dynamicArrive->getDynamicSteering());

		//boid->SetDynamicInput(dynamicAlign->getDynamicSteering());
		//boid->SetDynamicInput(dynamicWander->getDynamicSteering());
		/*
		if (pathIndex < path->size() - 1)
		{
			boid->Update(DeltaTime);
		}

		float dist = (boid->GetRidid()->position - target->GetRidid()->position).length();

		if (pathIndex < path->size() - 1 && dist <= 12.0f)
		{
			pathIndex++;
		}
		*/
		//std::cout << path->size() << std::endl;
	}

	if (target != NULL)
	{
		//RandomTargetPosition();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	float DeltaTime = ofGetLastFrameTime();

	breadTimer -= DeltaTime;
	if (breadTimer <= 0)
	{
		breadTimer = breadDelay;

		breads[breadIndex].position = boid->GetRidid()->position;
		if (breadIndex >= 99)
		{
			breadIndex = 0;
		}
		else
		{
			breadIndex++;
		}
	}

	if (boid != NULL) {
		boid->DrawBoid();
	}

	for (int i = 0; i < 100; i++)
	{
		breads[i].DrawBread();
	}
	
	if (target != NULL)
	{
		//target->DrawBoid();
	}

	if (finalTarget != NULL && Treenode != 1)
	{
		finalTarget->DrawBoid();
	}
	
	level->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::RandomTargetPosition()
{
	if (boid->GetRidid()->orientation < 1.5708f) // 0 - 90 degrees
	{
		target->GetRidid()->position.y = sinf(boid->GetRidid()->orientation) * 45;
		target->GetRidid()->position.x = cosf(boid->GetRidid()->orientation) * 45;

	}
	else if (boid->GetRidid()->orientation < 3.14159f) // 90 - 180 degrees
	{
		target->GetRidid()->position.x = -sinf(boid->GetRidid()->orientation - 1.5708f) * 45;
		target->GetRidid()->position.y = cosf(boid->GetRidid()->orientation - 1.5708f) * 45;

	}
	else if (boid->GetRidid()->orientation < 4.71239f) // 180 - 270 degrees
	{
		target->GetRidid()->position.y = -sinf(boid->GetRidid()->orientation - 3.14159f) * 45;
		target->GetRidid()->position.x = -cosf(boid->GetRidid()->orientation - 3.14159f) * 45;

	}
	else if (boid->GetRidid()->orientation < 6.28319f) // 270 - 360 degrees
	{
		target->GetRidid()->position.x = sin(boid->GetRidid()->orientation - 4.71239f) * 45;
		target->GetRidid()->position.y = -cosf(boid->GetRidid()->orientation - 4.71239f) * 45;

	}

	target->GetRidid()->position.x += RandomBinomial();
	target->GetRidid()->position.y += RandomBinomial();

	target->GetRidid()->position += boid->GetRidid()->position;
}

float ofApp::RandomBinomial()
{
	return ofRandom(0.0f, 2.0f) - ofRandom(0.0f, 2.0f);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


