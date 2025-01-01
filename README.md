**Window-Size Controller**
Created by Henri Laitinen around September 2024

**Introduction**
The goal of this project was to create an application that controls the window sizes of open applications on a computer. The initial idea was to eventually integrate this with a hardware gadget, such as a Raspberry Pi, that could serve as a dedicated control panel. While the hardware part was not completed due to time, budget, and practicality constraints, the software side was mostly finished and functional.

**How to Use**
To test this project, follow these steps:

-Run the MultipleClientServer: This will launch the TCP server used for communication between components.

-Run the ControlAppClient: This component handles the window resizing on the "target" computer.

-Run the ControlApp: This launches the user interface (UI), allowing you to interact with the system. You can adjust window sizes, and pressing Enter will apply the changes to the windows on your computer.


  **NOTE**

This application is optimized for my personal computer. Specific apps running in the background are blocked to maintain a manageable list of controllable windows.
A demonstration video is available in this repository.


**Software Components**
The software consists of three parts:

1. MultipleClientServer
A simple TCP server that facilitates communication between the other components.
It is barebones, with no security measures, as it was my first attempt at creating a TCP server. The implementation closely follows online guides.
The server's sole purpose is to relay messages between the components.

2. ControlAppClient
This component handles the actual window resizing.
It consists of:
Main script: Runs the TCP client to communicate with the server.
Header script: Provides helper functions, such as receiveMessage.
Upon receiving resize instructions, the client resizes the windows based on the specified dimensions using the windows.h header (WinAPI).
Sends periodic updates to other components, reporting the number of open windows to keep the UI in sync.

3. ControlApp
Provides the user interface for adjusting window sizes.
Developed using SFML, with UI design informed by space reserved for future features.
Uses periodic updates (every 2.5 seconds) to reflect the current number of open windows.
Though not fully complete according to the original plan, it is functional.


**What I Learned**
This project was a tremendous learning experience, teaching me:

Application Communication:
Setting up basic client-server communication using TCP protocol.

Windows API:
Learning how to use windows.h to interact with and control application windows.

User Interface Development:
Creating an interactive UI with SFML and planning for feature expansion.
While not fully finished, I am proud of the progress and the knowledge gained during this project. Many late nights were spent troubleshooting and building, and I enjoyed every moment.

**Future Plans**
There are several features I would like to implement or improve:

User Interface Enhancements:
Enable custom sorting of windows in the UI.
Display window names to help users identify which windows are being controlled.

Security Improvements:
Add authentication or encryption to the server-client communication for better security.

Hardware Integration:
Revive the original plan to implement this on a hardware gadget, such as a Raspberry Pi.
Although these features remain unimplemented for now, I designed the current system with expandability in mind, so adding them should be feasible in the future.

