#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include "windows.h"
#include <string>
using namespace std;



class windowGui
{

public:
	windowGui();

	//adds one rectangeShape to the rectangles vector
	//is ran as mannny times as needed to achieve right ammount of rectangels
	void addWindow();

	//Function that removes a rec if needed;
	void removeWindow();

	//Rearange windows to pre thought places according to the ammount of windows
	void rearangeRects();

	//function to put one screen to full screen when wanted
	void fullScreen(sf::RectangleShape* rec);

	vector<sf::RectangleShape*> returnRectangles();

	//moves pulltaps according to basic models
	void createPulls();

	//Return vecctor containing the sf::rectangleShapes of Pulltaps
	vector<sf::RectangleShape> returnPulls();


	//Makes moves when middle Pullltap is being moved
	void middleMove(int newXPosition, int newYPosition);

	//makes moves when left Pulltap is being moved
	void leftMove(int newXPosition, int newYPosition);

	//Makes moves when right Pulltap is being moved
	void rightMove(int newXPosition, int newYPosition);

	//return vectors of size and positions as int:s for windows resdizing
	string resizingMessage();

	void setSprites();

	vector<sf::Sprite> returnSprites();


	//Return the size of the ractangles vector aka the amount of windows already drawn
	int amountOfOpenWindows();

	//Checks witch window rectangles already has textures set and set for the rest of them
	void setBackgroundTextures();

	//Initializing Pulltap things (rectangleShape, orientation)
	//orientation 0=standing, 1=laying
	sf::RectangleShape middlePull;
	sf::RectangleShape leftPull;
	sf::RectangleShape rightPull;
	

private:
	vector<sf::RectangleShape*> rectangles;

	//For textures
	sf::Texture backgroundTexture1;
	sf::Texture backgroundTexture2;
	sf::Texture backgroundTexture3;
	sf::Texture backgroundTexture4;
	vector<sf::Texture> backgroundTextures;

	//Textures for the window numbers
	sf::Texture texture_1;
	sf::Texture texture_2;
	sf::Texture texture_3;
	sf::Texture texture_4;

	//Texture for the pulltaps
	sf::Texture pullTapTexture;

	//Vector where sprites are held so easy to handle
	vector<sf::Sprite> sprites;

	//Sprites for textures
	//Sprites wont be deleted, only moved out of the screen
	sf::Sprite texture_1_Sprite;
	sf::Sprite texture_2_Sprite;
	sf::Sprite texture_3_Sprite;
	sf::Sprite texture_4_Sprite;

	//Original position of sprites so easy to reset if rectang deleted
	sf::Vector2f spriteOriginalPos = { -100,-100 };



	
	int middleOrientation;
	int leftOrientation;
	int rightOrientation;

	//The positions of different borders of apps, For now these three
	int verticalPos=0;
	int rightHorizontalPos = 0;
	int leftHorizontalPos = 0;

	//saved value of guis "fullscreen" dimentions
	int fullWidth = 480;
	int fullHeight = 270;

	//Changing color of each added window rec
	vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta };
	int colorIndex = 0;

	//Difference value used to move windows
	int difference = 0;

	
	//Vector of the position we are moving right now (used in xxxMove() functions)
	sf::Vector2f movingWindowSize;

	int movingXValue;
	int movingYValue;

	int movingXPos;
	int movingYPos;

	//Function to update the position of the pulltaps and values helping that function
	void updatePulls();
	int pullUpdateX;
	int pullUpdateY;


	int returnSizeX;
	int returnSizeY;
	int returnPosX;
	int returnPosY;

	sf::Vector2u textureSize;
	sf::IntRect texInfo;

};

