# window-size-controller
****This project was created by Henri Laitinen****
**INtruction for using**
If you want to test this project please follow these instructions: first run the MultipleClientServer, this will launch the TCP server used for communication
Second run the COntrollAppClient, this will control the windows izing on ou "target" computer.
third run the controlApp, this will launch an user interface you can inter act witn. You can change the window sizes and if you press enter the window sizes on your computer will change.
**NOTE** This application is optimized for my personal computer as I have blocked specificly named apps that are runninng on the background, so I only get a manageable amount of apps to control.
I have also uploaded an demonstration video on this repotory.

**INTRO:** This projects goal was to create an application that could be used to control the window sizes of your open applications.
The original plan was to eventually build a desktop gadget that the control application would be run on, like rasperry bi, that would communicate with you computer while controlling the window sizes
The hardware part was never achieved mostly due to lack of time, money and the fact of this being quite gimmmicky so not worth putting more money and effort into
The software side was mostly completed.

The software:
  The entirety of the software consist of three parts: a client on the target computer controlling the windows, a server running on the target computer or the gadget and the main controlApp runnign on the gadget
  Keeping in mind that the hardware awas not finnished all of these codes can be run on the "target" computer. 
  For the communication between the different application I learnd to set up very simple server using TCP protocol.

  **PART 1: MultipleClienServer**
  IN this part I created an very simple Tcp protocol server that allows me to connect the two other part of the software. 
  The server is really really bare bones and does not have any security mearsurement as this was the first ever TCp thing I ever created, and awas creted pretty much straight following an guide
  This part of the code does not have anything else as its job is to just relay the messages from one part of the software to another

  **PART 2: ControlAppClient**
  In this part, we handel the actual window resizing. This part consist of main script and an header script. In the main script we run the stcp client that is connected to the server and an function  receiveMEssage
  That will check the incomming messages and answer to them correctly. If the incomming message tells this code to resize the windows, it will take the given dimension fot the windows and resize them. 
  For the window resizing I am using windows.h header file that is an ready made header file used for WinAPI. Using this file I can control all the windows on my screen. 
  The clients also send to eachother interval checks this client will send the number of open windows to the other client so it can keep the user interface updated.

  **PART 3: ControlApp**
  This part of the software provides us the user interface that the user usese to decide what size windows he wants. For the user interface I have used SFML and my amazing graphics desiner skills.
  Using the interval check this client will know how many application are open on the computer and update the user interface according to that knowledge. The intervale messages are sent every 2.5 seconds
  This part is the most complex and is still not compleatly finnished, atleast according to my original plans, but still works fine.


**What I have learned**
  This project taught me alot about the communications between different applications and about the windows.h. Although I never fully finished this project I am still happy about how much I learned from this
  I might someday return to this as I really enjoyed making this project and spend many night on it.

**Future plan about this project**
  There are a lot of things I still have not achieved in this project yet. Most notably the hardware, but also in the software. 
  One big thing for the software that I want to update some day is the way the windows are presented for the user on the user inteface. Now they are always in the same order and that order cant be changed.
  In the future I want to  implement a feature where the user can choose the layout in which the windows are sorted using this application. Luckily I had this in mind when making this project and some features are already implemented, 
  just not fully. Another feature I would like to add is a list of the names of the windows on the user inter´face so the user actualy know what the different windows on the UI are. 
  Both of these features were in my original plans, which is why the ui look a bit funny as the actually working part is kind of in the side, as I have reserved space for the upcomming features
  Another feature that would be good is to add some security check for the communication part, ie. in the server and cliant parts of the software
