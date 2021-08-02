#include "GameLevel.h"

GameLevel::GameLevel(const std::filesystem::path& path)
{
	this->levelWidth = -1.0f;
	this->levelHeight = -1.0f;

	float tileSize = -1.0f;
	int numberOfRows = -1;
	int numberOfCols = -1;

	bool sizeDefParsed = false;
	int numRowsParsed = 0;

	//std::cout << "Read Map" << std::endl;
	ofBuffer buffer = ofBufferFromFile(ofFile(ofToDataPath(path)));
	for (std::string line : buffer.getLines())
	{
		//std::cout << line << "\n";
		std::vector<std::string> lineSplit = ofSplitString(line, " ");
		char* firstChar = const_cast<char*>(lineSplit[0].c_str());
		std::string rowSpec;

		switch (*firstChar)
		{
		case COMMENT_LINE:
			break;
		case SIZEDEF_LINE:
			if (lineSplit.size() == 4)
			{
				this->levelWidth = std::stof(lineSplit[1]);
				this->levelHeight = std::stof(lineSplit[2]);
				tileSize = std::stof(lineSplit[3]);
				numberOfRows = this->levelHeight / tileSize;
				numberOfCols = this->levelWidth / tileSize;

				this->levelTileGraph = new TileGraph(numberOfRows, numberOfCols, tileSize);
			}
			sizeDefParsed = true;
			break;
		case ROWDEF_LINE:
			if (++numRowsParsed >= numberOfRows)
			{
				break;
			}

			if (sizeDefParsed == true)
			{
				if (lineSplit[1].length() == numberOfCols)
				{
					rowSpec = lineSplit[1];

					for (int colChar = 0; colChar < lineSplit[1].length(); colChar++)
					{
						char colSpec = lineSplit[1].at(colChar);

						switch (colSpec)
						{
						case BLANK_TILE:
							this->levelTileGraph->setTileValue(numRowsParsed - 1, colChar);
							break;
						case BLOCK_TILE:
							break;
						}
					}
				}
			}
			break;
		}
	}
	/*
	for (int i = 0; i < numberOfCols; i++)
	{
		for (int j = 0; j < numberOfRows; j++)
		{
			int nodeId = this->levelTileGraph->getTileValue(j, i);
			std::cout << "[" << nodeId << "] ";
		}
		std::cout << "\n\n";
	}
	*/
	//this->levelTileGraph = new TileGraph();
}

GameLevel::~GameLevel()
{
	delete this->levelTileGraph;
}

void GameLevel::update(float deltaTime)
{
}

void GameLevel::draw()
{
	for (int col = 0; col < this->levelTileGraph->getCols(); ++col) 
	{
		for (int row = 0; row < this->levelTileGraph->getRows(); ++row)
		{
			if (this->levelTileGraph->getTileValue(row, col) == TileGraph::TILE_BLOCKED)
			{
				//draw block
				float xPos = col * levelTileGraph->getTileSize();
				float yPos = row * levelTileGraph->getTileSize();

				drawBlock(xPos, yPos, levelTileGraph->getTileSize());
			}
		}
	}
}

void GameLevel::drawBlock(float xPos, float yPos, float tileSize)
{
	ofPushMatrix();
	ofTranslate(xPos, yPos);
	ofSetColor(0, 0, 0);
	ofDrawRectangle(0, 0, tileSize, tileSize);
	ofPopMatrix();
}
