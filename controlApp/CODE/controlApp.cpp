// controlApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>

#include <WinSock2.h>
#include "windows.h"
#include <WS2tcpip.h>

#include <string>
#include "mainFunctions.h"
#include "windowGui.h"
#include <thread>
#pragma comment (lib, "ws2_32.lib")



using namespace std;
int openWindowNum = 0;
bool intervalMsgReturned = true;
bool resizeBool = true;
char buf[4096];

string incommingMessage;

void receiveMessages(SOCKET sock) {
    
    while (true) {
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived > 0) {
            incommingMessage = string(buf, 0, bytesReceived);
            if (incommingMessage.substr(12, 2) == "//") {
                if (incommingMessage.substr(14, 1) == "#") {
                    openWindowNum = stoi(incommingMessage.substr(15));

                    cout << "interval chack returned" << openWindowNum <<endl;
                    intervalMsgReturned = true;
                }
                else if (incommingMessage.substr(14, 1) == "&") {
                    cout << "Resixing done!" << endl;
                    resizeBool = true;
                }
            }
        }
    }
}



void main() {
    string ipAddr = "127.0.0.1"; //Server IP
    int port = 54000;// listening port num

    //Init Winsoc
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wResult = WSAStartup(ver, &data);
    if (wResult != 0) {
        cerr << "Cant start winsock" << endl;
        return;
    }

    //create sock
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "cant create socket" << endl;
        WSACleanup();
        return;
    }

    //Filll in a hint struck
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);

    //connect to server
    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        cerr << "Cant connect to server" << endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    int acceptRecv = recv(sock, buf, 4096, 0);
    if (acceptRecv > 0) {
        cout << string(buf, 0, acceptRecv) << endl;
    }
    // Start a thread to continuously receive messages from the server
    thread receiver(receiveMessages, sock);


    
	sf::RenderWindow mainWindow(sf::VideoMode(480 + 150, 270 + 75), "Main", sf::Style::Default); //"windowGui" is 480x270           
    mainWindow.setFramerateLimit(60);

    //time limit for interval when to recheck window ammount so we wont overload 
    sf::Clock windowCheckClk;
    sf::Time checkElaps = sf::Time::Zero;
    sf::Time checkInterval = sf::seconds(2.5);

    //Time limit for moving shapes when mouse button pressed
    //(dont want to move too much to reduce load)
    sf::Clock guiRefreshClock;
    sf::Time guiRefreshElaps = sf::Time::Zero;
    sf::Time guiRefresLimit = sf::milliseconds(50);

    //number of currently checked windows to know if ammount changed since last check
    
    int difference = 0;

    //initialice the Gui class that creates all the "windows" on the empty renderWindow
    windowGui Gui;

    //Lets set up clock that resets the intervalMsgReturn bool if too long has passed
    //(Bool that checks if the interval window ammount message has been responded to before sending a nother one)
    //This can happen for example if the controlApp builds before controlAppClient and controll app sends message to the space and never 
    //can receive an answer. Lets set the limit to 2.5 seconds for now
    sf::Clock respondLimitClock;
    sf::Time respondLimitElaps = sf::Time::Zero;
    sf::Time respontLimitFlag = sf::seconds(2.5);



    while (mainWindow.isOpen())
    {
        //Update vector of open  windows once in 5 seconds (or whatever we set)
        checkElaps += windowCheckClk.restart();
        if (checkElaps >= checkInterval && intervalMsgReturned == true) {
            intervalMsgReturned = false;

            message = "//#";
            int sendResult = send(sock, message.c_str(), message.size() + 1, 0);
            if (sendResult == SOCKET_ERROR) {
                cerr << "Failed to send message to server!" << endl;
                break;
            }
            
            /* TEsting stuff
          
            for (const auto& win : openWindows) {
           
                std::wcout << L"Title: " << win.title << L" | Handle: " << win.hwnd << std::endl;
              
            }
            */
           //If ammount of window has changed, call function that creates Gui for that ammount
            //Each ammount has own class
            if (openWindowNum != Gui.amountOfOpenWindows()) {
                difference =openWindowNum-Gui.amountOfOpenWindows();
                
                if (openWindowNum <5) {
                    if (difference > 0) {
                        for (int i = 0; i < difference; ++i) {
                            Gui.addWindow();
                        }
                    }
                    else if (difference < 0) {
                        difference = difference * (-1);
                        for (int i = 0; i < difference; ++i) {
                            Gui.removeWindow();
                        }
                    }

                    Gui.rearangeRects();
                    Gui.createPulls();
                }
            }
            checkElaps = sf::Time::Zero;
        }

        respondLimitElaps+= respondLimitClock.restart();
        if (respondLimitElaps >= respontLimitFlag) {
            respondLimitElaps = sf::Time::Zero;
            intervalMsgReturned = true;
        }

        
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }else if (event.type == sf::Event::MouseButtonPressed) {
                if (openWindowNum > 1) {

                    sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);

             
                    //Check if mouse click hit pullTaps
                    if (Gui.leftPull.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        mousePressed = true;
                        leftHit = true;
                    }
                    else if (Gui.rightPull.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        mousePressed = true;
                        rightHit = true;
                    }
                    else if (Gui.middlePull.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        mousePressed = true;
                        middleHit = true;
                    }
                }
                


            }else if (event.type == sf::Event::MouseButtonReleased){
                middleHit = false;
                rightHit = false;
                leftHit = false;
                mousePressed = false;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && resizeBool == true) {
                    resizeBool = false;
                    message = "//&";
                    message += Gui.resizingMessage();
                    //cout << message << endl;
                    int sendResult = send(sock, message.c_str(), message.size() + 1, 0);
                    if (sendResult == SOCKET_ERROR) {
                        cerr << "Failed to send message to server!" << endl;
                        break;
                    }
                }

                if (event.key.code == sf::Keyboard::W) {
                    closesocket(sock);
                    WSACleanup();
                }
            }
        


        }

        //When refresElaps time has passed and mousePressed is true
        //aka left mouse button is pressed down after hitting pulltap
        guiRefreshElaps += guiRefreshClock.restart();
        if (mousePressed && guiRefresLimit <= guiRefreshElaps) {
            // !!BUg finding!! cout << "Moving " << sf::Mouse::getPosition(mainWindow).y<< endl; 

            //Mouse clicked middlepull
            if (middleHit) {
                //New positoins
                movingX = sf::Mouse::getPosition(mainWindow).x;
                movingY = sf::Mouse::getPosition(mainWindow).y;

                //Check if mouse position is in the allowed space
                //If is calls function that moves the right windows
                if (movingX > windowXLimitMin && movingX < windowXLimitMax) {
                    Gui.middleMove(movingX, movingY);
                }
                else if (movingX<windowXLimitMin){
                    movingX = windowXLimitMin;
                    Gui.middleMove(movingX, movingY);
                  
                }
                else if (movingX > windowXLimitMax) {
                    movingX = windowXLimitMax;
                    Gui.middleMove(movingX, movingY);
                   
                }
                

            }
            //mouse clicked left pulltap
            else if (leftHit) {
                //Position of mouse where it moved
                movingX = sf::Mouse::getPosition(mainWindow).x;
                movingY = sf::Mouse::getPosition(mainWindow).y;

                //Checks if mouse is in a allowed space
                //If is calls function in windowGui (Gui) that moves right windows corresponding to the pulltap
                if (movingY > windowYLimitMin && movingY < windowYLimitMax) {
                    Gui.leftMove(movingX, movingY);

                }
                else if (movingY <windowYLimitMin) {
                    movingY = windowYLimitMin;
                    Gui.leftMove(movingX, movingY);
                  
                }
                else if (movingY > windowYLimitMax) {
                    movingY = windowYLimitMax;
                    Gui.leftMove(movingX, movingY);
                   
                }
                
            }
            //If mouse clicked on the right pull tap
            else if (rightHit) {
                //position of mouse 
                movingX = sf::Mouse::getPosition(mainWindow).x;
                movingY = sf::Mouse::getPosition(mainWindow).y;
              
                //Checks if mouse is in the lowed space
                //If is then calls function that moves the right windows corresponding to the pul tap clicked. 
                if (movingY > windowYLimitMin && movingY < windowYLimitMax) {
                    Gui.rightMove(movingX, movingY);

                }
                else if (movingY < windowYLimitMin) {
                    movingY = windowYLimitMin;
                    Gui.rightMove(movingX, movingY);
                  
                }
                else if (movingY > windowYLimitMax) {
                    movingY = windowYLimitMax;
                    Gui.rightMove(movingX, movingY);
                  
                }
            }
        }
        //Set background textures
        Gui.setBackgroundTextures();

        //Set the sprites to correct places
        Gui.setSprites();

        //Clears the window, draws items and displays them
        mainWindow.clear();
        for (sf::RectangleShape* rec : Gui.returnRectangles()) {
            mainWindow.draw(*rec);
        }
        vector<sf::RectangleShape> pullTaps = Gui.returnPulls();
        for (sf::RectangleShape pulltap : pullTaps) {
            mainWindow.draw(pulltap);
        }
        for (sf::Sprite spriteDraw : Gui.returnSprites()) {
            mainWindow.draw(spriteDraw);
        }
        
        mainWindow.display();
    }
    ///*/
}
