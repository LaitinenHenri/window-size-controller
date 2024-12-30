#pragma once

#include <iostream>
#include <vector>
#include "windows.h"
#include <string>
#include <algorithm>

using namespace std;


//Vector that contains titles to apps wanted to ignore and not added to openWindows
//contains mostly apps realted to running this software or other useless appps
vector<wstring> unwantedTitles = {
    L"Grammarly Anchor Window",
    L"controlApp - Microsoft Visual Studio",
    L"Windowsin sy÷tekokemus",
    L"Program Manager",
    L"Windowsin syötekokemus",
    L"C:\\Users\\Käyttäjä\\OneDrive\\Tiedostot\\VS coding\\controlApp\\x64\\Debug\\controlApp.exe",
    L"Main",
    L"multipleClientServer - Microsoft Visual Studio",
    L"controlAppClient - Microsoft Visual Studio",
    L"C:\\Users\\Käyttäjä\\OneDrive\\Tiedostot\\VS coding\\controlAppClient\\x64\\Debug\\controlAppClient.exe",
    L"C:\\Users\\Käyttäjä\\OneDrive\\Tiedostot\\VS coding\\multipleClientServer\\x64\\Debug\\multipleClientServer.exe"
};

//Tranforms wstring (L"") to string and returns the srting
std::string wstring_to_string(const std::wstring& wstr) {
    std::string str(wstr.begin(), wstr.end());
    return str;
}

//Checks if the title of the app being handeled is on the unwantedTitles vector. 
//return true it it is (not added to openWindows)
bool isUnwantedTitle(const wstring title) {
    for (wstring badTitle : unwantedTitles) {
        if (title == badTitle) {
            return true;
        }
    }
    return false;
}
// This struct will store the handles and titles of the open windows
struct WindowInfo {
    HWND hwnd;
    std::wstring title; // Use wstring for wide characters
};

// Global vector to store all open windows
std::vector<WindowInfo> openWindows;

// Callback function used by EnumWindows to retrieve open windows
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    wchar_t title[256];
    if (IsWindowVisible(hwnd) && GetWindowTextW(hwnd, title, sizeof(title) / sizeof(title[0])) != 0) {
        std::wstring windowTitle(title);

        // Compare the window title with the unwanted title
        if (!isUnwantedTitle(windowTitle)) {
            openWindows.push_back({ hwnd, windowTitle });
        }
    }
    return TRUE; // Continue enumeration
}

// Function to enumerate open windows
void enumerateWindows() {
    openWindows.clear();
    EnumWindows(EnumWindowsProc, NULL);

    
}

// Function to resize a specific window by its title
void resizeWindowByTitle(const std::wstring& windowTitle, int width, int height) {
    for (const auto& win : openWindows) {
        if (win.title == windowTitle) {
            std::wcout << L"Resizing window: " << win.title << std::endl;
            // Resize the window using SetWindowPos or MoveWindow
            SetWindowPos(win.hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
            break;
        }
    }
}

void resizing(vector<vector<int>> sizePositionVector) {
    int index = 0;
    int horizontalEqualizer = 0;
    int verticalEqualizer = 0;

    for (WindowInfo win : openWindows) {
        if (index == 0) {
            horizontalEqualizer = 10;
            if (openWindows.size() == 4) {
                verticalEqualizer = 7;
            }
            else {
                verticalEqualizer = 0;
            }

        }
        else if (index == 1) {
            horizontalEqualizer = -10;
            if (openWindows.size() > 2) {
                verticalEqualizer = 7;
            }
            else {
                verticalEqualizer = 0;

            }
        }
        else if (index == 2) {
            horizontalEqualizer = -10;
            verticalEqualizer = -7;
        }
        else if (index ==3){
            horizontalEqualizer = 10;
            verticalEqualizer = -7;
        }


        vector<int> sizePos = sizePositionVector.at(index);
        ++index;
        ShowWindow(win.hwnd, SW_RESTORE);

        //SetWindowPos() function in english=>
        //SetWindowPos(win.hwnd, HWND_TOP, x position, y position, width, height, SWP_NOZORDER | SWP_FRAMECHANGED)
        SetWindowPos(win.hwnd, HWND_TOP, sizePos.at(0) * 4, sizePos.at(1) * 4, sizePos.at(2) * 4 + horizontalEqualizer, sizePos.at(3) * 4 + verticalEqualizer, SWP_NOZORDER | SWP_FRAMECHANGED);
        cout << sizePos.at(0) * 4 << " " << sizePos.at(1) * 4 << " " << sizePos.at(2) * 4 << " " << sizePos.at(3) * 4 << endl;
    }

}

void reshapeResizeCommand(string measurementsInStr) {
    vector<vector<int>> measurementsInVec = {};
    vector<int> innerVec = {};
    string breakdown="";
    int breakdownInt = 0;

    for (char character : measurementsInStr) {
        if (character == ';') {
            breakdownInt = stoi(breakdown);
            innerVec.push_back(breakdownInt);
            breakdown = "";
        }
        else if (character == ':') {
            breakdownInt = stoi(breakdown);
            innerVec.push_back(breakdownInt);
            breakdown = "";
            measurementsInVec.push_back(innerVec);
            innerVec = {};
        }
        else {
            breakdown += character;
        }
    }

    resizing(measurementsInVec);
}

