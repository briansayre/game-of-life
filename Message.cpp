#include <iostream>
using namespace std;

#include "Message.h"

// default constructor
Message::Message() {
    function = -1;
    message = " ";
    mouseX = 0;
    mouseY = 0;
}

// draws a string of characters on the display
Message::Message(int f, string m) {
    function = f;
    message = m;
    mouseX = 0;
    mouseY = 0;
}

// return function
int Message::getFunction() {
    return function;
}

// set function
void Message::setFunction(int f) {
    function = f;
}

// return message
string Message::getMessage() {
    return message;
}

// set message
void Message::setMessage(string m) {
    message = m;
}

// return mouse y position
int Message::getMouseY() {
    return mouseY;
}

// set mouse y position
void Message::setMouseY(int y) {
    mouseY = y;
}

// returns mouse x position
int Message::getMouseX() {
    return mouseX;
}

// set mouse x position
void Message::setMouseX(int x) {
    mouseX = x;
}

// Parses raw message to get function and file path
void Message::parseMessage(char* m, int length) {
    if (m[5] + 0 == 10) {
        string filePath = "";
        for (int j = 6; j < length; j += 2) {
            unsigned char c = (m[j] << 4) | (m[j + 1] << 0);
            filePath.push_back(c);
        }
        message = filePath;
        function = 10;
    } else {
        int type = m[6] + 0;
        if (type == 1) {
            mouseX = (m[7] * 4096) + (m[8] * 256) + (m[9] * 16) + m[10];
            mouseY = (m[11] * 4096) + (m[12] * 256) + (m[13] * 16) + m[14];
            function = decideFunction(mouseX, mouseY);
        }
    }
}

// Return function number based of position of mouse click
int Message::decideFunction(int x, int y) {
    if (x >= 650 && x <= 750) {
        if (y >= 25 && y <= 60) {  // step
            return 0;
        } else if (y >= 75 && y <= 110) {  // run
            return 1;
        } else if (y >= 125 && y <= 160) {  // pause
            return 2;
        } else if (y >= 175 && y <= 210) {  // reset
            return 3;
        } else if (y >= 225 && y <= 260) {  // random
            return 4;
        } else if (y >= 275 && y <= 310) {  // load
            return 5;
        } else if (y >= 325 && y <= 360) {  // quit
            return 6;
        } else if (y >= 425 && y <= 460) {  // 1
            return 7;
        } else if (y >= 475 && y <= 510) {  // 2
            return 8;
        } else if (y >= 525 && y <= 560) {  // 3
            return 9;
        }
    } else {
        return 11;
    }
    return -1;
}
