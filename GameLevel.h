#pragma once
#include <vector>
#include "GameObject.h"
#include "TileGraph.h"
#include "ofGraphics.h"
#include <filesystem>
#include "ofFileUtils.h"
#include "ofUtils.h"
#include <stdio.h>

class GameLevel {
	std::vector<GameObject*> levelGameObjects;

	float levelWidth = 0.0f;
	float levelHeight = 0.0f;

	static const char COMMENT_LINE = 'c';
	static const char SIZEDEF_LINE = 's';
	static const char ROWDEF_LINE = 'r';

	static const char BLOCK_TILE = '@';
	static const char BLANK_TILE = '.';


public:
	TileGraph* levelTileGraph;

	GameLevel(const std::filesystem::path& path);
	~GameLevel();
	void update(float deltaTime);
	void draw();

	void drawBlock(float xPos, float yPos, float tileSize);
};