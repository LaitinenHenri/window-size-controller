#include "windowGui.h"




/// Initialize the windowGui class, set up pull taps to priviously set models
windowGui::windowGui() {
	//Load background texture
	if (!backgroundTexture1.loadFromFile("back1.png")) {
		cout << "Error background texture" << endl;
	}if (!backgroundTexture2.loadFromFile("back2.png")) {
		cout << "Error background texture" << endl;
	}if (!backgroundTexture3.loadFromFile("back3.png")) {
		cout << "Error background texture" << endl;
	}if (!backgroundTexture4.loadFromFile("back4.png")) {
		cout << "Error background texture" << endl;
	}
	backgroundTextures.push_back(backgroundTexture1);
	backgroundTextures.push_back(backgroundTexture2);
	backgroundTextures.push_back(backgroundTexture3);
	backgroundTextures.push_back(backgroundTexture4);
	//LOad textures for sprites
	if (!texture_1.loadFromFile("label1.png")) {
		cout << "Error loading texture rect1" << endl;
	}if (!texture_2.loadFromFile("label2.png")) {
		cout << "Error loading texture rect2" << endl;
	}if (!texture_3.loadFromFile("label3.png")) {
		cout << "Error loading texture rect3" << endl;
	}if (!texture_4.loadFromFile("label4.png")) {
		cout << "Error loading texture rect4" << endl;
	}

	if (!pullTapTexture.loadFromFile("pullTap.png")) {
		cout << "Pull tap texture Error!" << endl;
	}

	texture_1_Sprite.setTexture(texture_1);
	texture_2_Sprite.setTexture(texture_2);
	texture_3_Sprite.setTexture(texture_3);
	texture_4_Sprite.setTexture(texture_4);

	sprites.push_back(texture_1_Sprite);
	sprites.push_back(texture_2_Sprite);
	sprites.push_back(texture_3_Sprite);
	sprites.push_back(texture_4_Sprite);

	for (sf::Sprite& sprite : sprites) {
		sprite.setOrigin({30,30});
		sprite.setPosition(spriteOriginalPos);
	}

	
	//Create all the puls and adjust their sizes
	//Sizes wont cnahge at all during run nor colors
	//LATER ADD TEXTURES
	middlePull.setSize({ 20,50 });
	middlePull.setOrigin(10, 25);
	//middlePull.setFillColor(sf::Color::White);


	leftPull.setSize({ 20,50});
	leftPull.setOrigin(10, 25);
	//leftPull.setFillColor(sf::Color::White);


	rightPull.setSize({ 20,50});
	rightPull.setOrigin(10, 25);
	//rightPull.setFillColor(sf::Color::White);

	middlePull.setTexture(&pullTapTexture);
	leftPull.setTexture(&pullTapTexture);
	rightPull.setTexture(&pullTapTexture);


}

//Adds one window (sf::RectangleShape). DOes not set position just creates it
void windowGui::addWindow() {
	sf::RectangleShape* newRec = new sf::RectangleShape;

	rectangles.push_back(newRec);
}

//Removes one window. Is called in main as many times as needed
void windowGui::removeWindow() {
	delete rectangles.back();
	rectangles.pop_back();
}

//Rearanges the windows to pre thought of positions to give "plain" start to new ammount of windows
void windowGui::rearangeRects() {
	int size = rectangles.size();

	//If only onw window it goes full screen
	//Maybe later you can size it as you want
	if (size == 1) {
		fullScreen(rectangles.at(0));
	}

	//sets 2 wectors new to each other 
	else if (size == 2) {

		sf::Vector2f* sizeRec = new sf::Vector2f;
		sizeRec->x = fullWidth / 2;  //480/2
		sizeRec->y = fullHeight;     //270

		rectangles.at(0)->setPosition(0, 0);
		rectangles.at(0)->setSize(*sizeRec);
		rectangles.at(1)->setPosition(fullWidth/2, 0);
		rectangles.at(1)->setSize(*sizeRec);

		delete sizeRec;

		verticalPos = rectangles.at(1)->getPosition().x;
	}
	//Sets one window to right , two the left on top of each other
	else if (size == 3) {
		sf::Vector2f* sizeRec = new sf::Vector2f;
		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight;      //270
		rectangles.at(0)->setPosition(0, 0);
		rectangles.at(0)->setSize(*sizeRec);

		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight/2;      //270
		rectangles.at(1)->setPosition(fullWidth / 2, 0);
		rectangles.at(1)->setSize(*sizeRec);
		
		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight/2;      //270
		rectangles.at(2)->setPosition(fullWidth / 2, fullHeight / 2);
		rectangles.at(2)->setSize(*sizeRec);
		
		delete sizeRec;
		rightHorizontalPos = rectangles.at(2)->getPosition().y;
		verticalPos = rectangles.at(1)->getPosition().x;
	}

	//Sets the 4 windwos to corners
	else if (size == 4) {
		sf::Vector2f* sizeRec = new sf::Vector2f;
		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight/2;      //270
		rectangles.at(0)->setPosition(0, 0);
		rectangles.at(0)->setSize(*sizeRec);

		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight / 2;      //270
		rectangles.at(1)->setPosition(fullWidth / 2, 0);
		rectangles.at(1)->setSize(*sizeRec);

		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight / 2;      //270
		rectangles.at(2)->setPosition(fullWidth / 2, fullHeight / 2);
		rectangles.at(2)->setSize(*sizeRec);

		sizeRec->x = fullWidth / 2;       //480/2
		sizeRec->y = fullHeight / 2;      //270
		rectangles.at(3)->setPosition(0,fullHeight/2);
		rectangles.at(3)->setSize(*sizeRec);

		delete sizeRec;
		rightHorizontalPos = rectangles.at(2)->getPosition().y;
		verticalPos = rectangles.at(1)->getPosition().x;
		leftHorizontalPos = rectangles.at(3)->getPosition().y;
	}



}

//Sets window that is arg to full screen
void windowGui::fullScreen(sf::RectangleShape* rec) {
	rec->setPosition(0, 0);
	rec->setSize({ 480,270 });


}

//Returns the vector that contains the pointers to all of the windows (sf::RectangleShape)
vector<sf::RectangleShape*> windowGui::returnRectangles() {
	return rectangles;
}


//Moves pulltaps, works now on only pre set models
void windowGui::createPulls() {
	//On preset model the pull positions will always be bindede to a specific windwow border
	//middlePull is bided to verticalPos, leftPull to leftHorizontalPos, rightPull to rightHorizontalPos
	int size =rectangles.size();
	if (size == 2) {
		middlePull.setPosition(verticalPos, fullHeight / 2);
		middleOrientation = 0;
	}if (size == 3) {
		middlePull.setPosition(verticalPos, fullHeight / 2);
		middleOrientation = 0;

		rightPull.setPosition(verticalPos+(fullWidth-verticalPos)/2, rightHorizontalPos);
		rightPull.setRotation(90);
		rightOrientation = 1;
	}if (size == 4) {
		middlePull.setPosition(verticalPos, fullHeight / 2);
		middleOrientation = 0;

		rightPull.setPosition(verticalPos + (fullWidth - verticalPos) / 2, rightHorizontalPos);
		rightPull.setRotation(90);
		rightOrientation = 1;

		leftPull.setPosition(verticalPos / 2, leftHorizontalPos);
		leftPull.setRotation(90);
		leftOrientation = 1;
	}

}

// returns vector that contains all the pullTaps (sf::RectangleShape)
vector<sf::RectangleShape> windowGui::returnPulls() {
	vector<sf::RectangleShape> pulls;
	int size = rectangles.size();
	if(size == 2) {
		pulls.push_back(middlePull);
	}
	else if (size == 3) {
		pulls.push_back(rightPull);
		pulls.push_back(middlePull);
	}
	else if (size == 4) {
		pulls.push_back(rightPull);
		pulls.push_back(middlePull);
		pulls.push_back(leftPull);
	}

	return pulls;

}



//MOves the middle pull tap
void windowGui::middleMove(int newXPosition, int newYPosition) {
	
	if (middleOrientation == 0) {
		difference = newXPosition - verticalPos;

		verticalPos = newXPosition;

		

		
		if (difference > 0 ) {
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {
				if (index == 0 || index == 3) {
					movingXValue = window->getSize().x;
					movingYValue = window->getSize().y;
					movingWindowSize.x = movingXValue + difference;
					movingWindowSize.y = movingYValue;
					window->setSize(movingWindowSize);
				}
				else if (index == 1 || index == 2) {
					movingXValue = window->getSize().x;
					movingYValue = window->getSize().y;
					movingWindowSize.x = movingXValue - difference;
					movingWindowSize.y = movingYValue;

					movingXPos = window->getPosition().x + difference;
					movingYPos = window->getPosition().y;

					window->setSize(movingWindowSize);
					window->setPosition(movingXPos, movingYPos);
				}



				++index;
			}
		}
		else if (difference < 0) {
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {
				if (index == 0 || index == 3) {
					movingXValue = window->getSize().x;
					movingYValue = window->getSize().y;
					movingWindowSize.x = movingXValue + difference;
					movingWindowSize.y = movingYValue;
					window->setSize(movingWindowSize);
				}
				else if (index == 1 || index == 2) {
					movingXValue = window->getSize().x;
					movingYValue = window->getSize().y;
					movingWindowSize.x = movingXValue - difference;
					movingWindowSize.y = movingYValue;

					movingXPos = window->getPosition().x + difference;
					movingYPos = window->getPosition().y;

					window->setSize(movingWindowSize);
					window->setPosition(movingXPos, movingYPos);
				}



				++index;
			}
		}
		updatePulls();


	}
		
	else if (middleOrientation == 1) {
		difference = /*horizontal middle pos???*/ -newYPosition;
	}

}

//Moves the windows on the left side of the scree, Windows 0 and 3
void windowGui::leftMove(int newXPosition, int newYPosition) {
	if (leftOrientation == 0) {
		//For later
	}
	else if (leftOrientation == 1) {
		//The difference of the new and old position
		difference = leftHorizontalPos - newYPosition;
		leftHorizontalPos = newYPosition;

		//Difference is positive so new "borde" is above the old "border"
		if (difference > 0) {
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {
				//Only move the left side windows
				if (index == 0 || index == 3) {
					if (index == 0) {
						//SEt the new sizes (only horizontal movement so only y changes)
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y - difference;
						window->setSize(movingWindowSize);
					}
					else if (index == 3) {
						//SEt the new sizes (only horizontal movement so only y changes)
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y + difference;
						window->setSize(movingWindowSize);
						
						//Bottom window also has to be moved due to the origin being on the top left corner
						//(avoid overlap)
						movingXPos = window->getPosition().x;
						movingYPos = window->getPosition().y - difference;
						window->setPosition(movingXPos, movingYPos);
					}
				}
				++index;
			}
		}//If diffference is negative the new "border" isbelov the old border
		else if (difference < 0) { /*line moving down */
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {

				//Only indexes 0 and 3 aka the windows on the left side
				if (index == 0 || index == 3) {
					if (index == 0) {
						//Set the new window sizes (only horizontal moving so only y changes)
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y - difference; // double negative
						window->setSize(movingWindowSize);
					}
					else if (index == 3) {
						//Set the new window sizes (only horizontal moving so only y changes)
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y + difference;
						window->setSize(movingWindowSize);

						//The bottom window (index == 3) also has to be moved
						//due to rigin being on the top left corner (awoid overlap)
						movingXPos = window->getPosition().x;
						movingYPos = window->getPosition().y - difference; //double negative
						window->setPosition(movingXPos, movingYPos);
					}
				}
				++index;
			}
		}
		updatePulls();


	}

}

//Moves windows on the right side of windows (indexes 1 and 2)
void windowGui::rightMove(int newXPosition, int newYPosition) {
	if (rightOrientation == 0) {
		//For later
	}
	else if (rightOrientation == 1) {
		difference = rightHorizontalPos - newYPosition;
		rightHorizontalPos = newYPosition;
		
		//If difference is positive the new border of windows will be above old border
		if (difference > 0) { 
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {
				//Only effects window 1 and 2
				if (index == 1 || index == 2) {
					if (index == 1) {
						//Set new sizes, nly horizontal movement so only y changes
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y - difference;
						window->setSize(movingWindowSize);
					}
					else if (index == 2) {
						//Set new sizes, nly horizontal movement so only y changes
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y + difference;
						window->setSize(movingWindowSize);

						//Bottom window also has to be moved due to orgin being on the top left corner
						//Avoids overlap
						movingXPos = window->getPosition().x;
						movingYPos = window->getPosition().y - difference;
						window->setPosition(movingXPos, movingYPos);
					}
				}
				++index;
			}
		}//If difference is negative the new border will be belov the old border
		else if (difference < 0) { 
			int index = 0;
			for (sf::RectangleShape* window : rectangles) {
				//only move & resize windows 1 and 2
				if (index == 1 || index == 2) {
					if (index == 1) {
						//set new size only horizontal movement so only y changes
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y - difference; // double negative
						window->setSize(movingWindowSize);
					}
					else if (index == 2) {
						//set new size only horizontal movement so only y changes
						movingWindowSize.x = window->getSize().x;
						movingWindowSize.y = window->getSize().y + difference;
						window->setSize(movingWindowSize);

						//For bottom window also move the window
						//due to origin being on the top left
						//AVoid overlapping
						movingXPos = window->getPosition().x;
						movingYPos = window->getPosition().y - difference; //double negative
						window->setPosition(movingXPos, movingYPos);
					}
				}
				++index;
			}
		}
		updatePulls();
	}
}

//Updates the position of the pulltaps
void windowGui::updatePulls() {
	if (middleOrientation == 0) {
		//Sets the new position to the vertical line position
		pullUpdateY = middlePull.getPosition().y;
		if (middlePull.getPosition().x != verticalPos) {
			middlePull.setPosition(verticalPos, pullUpdateY);
		}
		
	}
	else if (middleOrientation == 1) {
		//For later
	}

	if (leftOrientation == 0) {
		//For later
	}
	else if (leftOrientation == 1) {
		//SEts new position to the updated left horizontal line position 
		pullUpdateX = verticalPos / 2;
		pullUpdateY = leftHorizontalPos;
		leftPull.setPosition(pullUpdateX, pullUpdateY);

	}

	if (rightOrientation == 0) {
		//For later
	}
	else if(rightOrientation == 1){
		//sets position to the updates right horizontal line position
		pullUpdateX = verticalPos + (fullWidth - verticalPos) / 2;
		pullUpdateY = rightHorizontalPos;
		rightPull.setPosition(pullUpdateX, pullUpdateY);
	}
}

//Returns vector inside a vector that contains size and position information of the windows on the gui
//Information is in standarded order
//1. x Position, 2. y position, ´3. width, 4. height
//Vectors are in the same order as in rectangles vector
string windowGui::resizingMessage(){
	string windowInfo="";
	string returnMessage="";
	for (sf::RectangleShape* window : rectangles) {
		windowInfo += to_string(window->getPosition().x);
		windowInfo += ";";
		windowInfo += to_string(window->getPosition().y);
		windowInfo += ";";
		windowInfo += to_string(window->getSize().x);
		windowInfo += ";";
		windowInfo += to_string(window->getSize().y);
		windowInfo += ":";

		returnMessage += windowInfo;
		windowInfo = "";
		

	}

	return returnMessage;
}

void windowGui::setSprites() {
	int index = 0;

	for (sf::RectangleShape* rectangle_setSprite : rectangles) {
		
		sf::Vector2f spritePosition = rectangle_setSprite->getPosition();

		sf::Vector2f spritePositionSize = rectangle_setSprite->getSize();
		spritePosition.x = spritePosition.x + spritePositionSize.x / 2;
		spritePosition.y = spritePosition.y + spritePositionSize.y / 2;
		sprites.at(index).setPosition(spritePosition);
		++index;
	}

	while (index < 4) {
		sprites.at(index).setPosition(spriteOriginalPos);
		++index;
	}


}



vector<sf::Sprite> windowGui::returnSprites() {
	return sprites;
}

int windowGui::amountOfOpenWindows() {
	return rectangles.size();
}


void windowGui::setBackgroundTextures() {
	int index = 0;
	for (sf::RectangleShape* rectangleInCase : rectangles) {
		
		if (rectangleInCase->getTexture() == nullptr) {
			rectangleInCase->setTexture(&backgroundTextures.at(index));
		}
		++index;
	}

}