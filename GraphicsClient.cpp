#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

using namespace std;

#include "GraphicsClient.h"
#include "Message.h"

// GC constructor
GraphicsClient::GraphicsClient(string url, int port) {
    this->url = url;
    this->port = port;
    // connect to websocket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket\n");
        exit(-1);
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    const char* cstr = url.c_str();
    if (inet_pton(AF_INET, cstr, &serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        exit(1);
    }
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Connection Failed \n");
        exit(1);
    }
    setBackgroundColor(214, 217, 223);
    clear();
    drawButtons();
    repaint();
}

// GC copy constructor
GraphicsClient::GraphicsClient(const GraphicsClient& origGraphicsClient) {
    url = origGraphicsClient.url;
    port = origGraphicsClient.port;
    sockfd = origGraphicsClient.sockfd;
}

// GC deconstructor
GraphicsClient::~GraphicsClient() {
    this->setBackgroundColor(0, 0, 0);
    this->clear();
    this->setDrawingColor(250, 250, 250);
    this->drawString(10, 20, "Socket closed. Beep. Boop.");
    this->repaint();
    close(sockfd);  /// close socket
}

// GC operator= method
GraphicsClient& GraphicsClient::operator=(const GraphicsClient& objToCopy) {
    if (this != &objToCopy) {
        url = objToCopy.url;
        port = objToCopy.port;
        sockfd = objToCopy.sockfd;
    }
    return *this;
}

// sets the background color of the associated display
void GraphicsClient::setBackgroundColor(int r, int g, int b) {
    char message[12];
    message[0] = 0xFF;             // SYNC
    message[1] = 0x00;             // Length
    message[2] = 0x00;             // Length
    message[3] = 0x00;             // Length
    message[4] = 0x07;             // Length
    message[5] = 0x02;             // Function
    message[6] = (r >> 4) & 0xF;   // red
    message[7] = (r >> 0) & 0xF;   // red
    message[8] = (g >> 4) & 0xF;   // green
    message[9] = (g >> 0) & 0xF;   // green
    message[10] = (b >> 4) & 0xF;  // blue
    message[11] = (b >> 0) & 0xF;  // blue
    send(sockfd, message, 12, 0);
}

// set the color that objects will be drawn at until another setDrawingColor call is made.
void GraphicsClient::setDrawingColor(int r, int g, int b) {
    char message[12];
    message[0] = 0xFF;             // SYNC
    message[1] = 0x00;             // Length
    message[2] = 0x00;             // Length
    message[3] = 0x00;             // Length
    message[4] = 0x07;             // Length
    message[5] = 0x06;             // Function
    message[6] = (r >> 4) & 0xF;   // red
    message[7] = (r >> 0) & 0xF;   // red
    message[8] = (g >> 4) & 0xF;   // green
    message[9] = (g >> 0) & 0xF;   // green
    message[10] = (b >> 4) & 0xF;  // blue
    message[11] = (b >> 0) & 0xF;  // blue
    send(sockfd, message, 12, 0);
}

// clears the display to the background color
void GraphicsClient::clear() {
    char message[6];
    message[0] = 0xFF;  // SYNC
    message[1] = 0x00;  // Length
    message[2] = 0x00;  // Length
    message[3] = 0x00;  // Length
    message[4] = 0x01;  // Length
    message[5] = 0x01;  // Function
    send(sockfd, message, 6, 0);
}

// sets the pixel at the location to the color
void GraphicsClient::setPixel(int x, int y, int r, int g, int b) {
    char message[20];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x00;              // Length
    message[4] = 0x0F;              // Length
    message[5] = 0x03;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (r >> 4) & 0xF;   // red
    message[15] = (r >> 0) & 0xF;   // red
    message[16] = (g >> 4) & 0xF;   // green
    message[17] = (g >> 0) & 0xF;   // green
    message[18] = (b >> 4) & 0xF;   // blue
    message[19] = (b >> 0) & 0xF;   // blue
    send(sockfd, message, 20, 0);
}

// draws a rectangle at the specified coordinates to the color
void GraphicsClient::drawRectangle(int x, int y, int w, int h) {
    char message[22];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x01;              // Length
    message[4] = 0x01;              // Length
    message[5] = 0x07;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (w >> 12) & 0xF;  // w
    message[15] = (w >> 8) & 0xF;   // w
    message[16] = (w >> 4) & 0xF;   // w
    message[17] = (w >> 0) & 0xF;   // w
    message[18] = (h >> 12) & 0xF;  // h
    message[19] = (h >> 8) & 0xF;   // h
    message[20] = (h >> 4) & 0xF;   // h
    message[21] = (h >> 0) & 0xF;   // h
    send(sockfd, message, 22, 0);
}

// draws a filled rectangle at the position
void GraphicsClient::fillRectangle(int x, int y, int w, int h) {
    char message[22];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x01;              // Length
    message[4] = 0x01;              // Length
    message[5] = 0x08;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (w >> 12) & 0xF;  // w
    message[15] = (w >> 8) & 0xF;   // w
    message[16] = (w >> 4) & 0xF;   // w
    message[17] = (w >> 0) & 0xF;   // w
    message[18] = (h >> 12) & 0xF;  // h
    message[19] = (h >> 8) & 0xF;   // h
    message[20] = (h >> 4) & 0xF;   // h
    message[21] = (h >> 0) & 0xF;   // h
    send(sockfd, message, 22, 0);
}

// clears (sets the pixels to the background color) at the location and size
void GraphicsClient::clearRectangle(int x, int y, int w, int h) {
    char message[22];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x01;              // Length
    message[4] = 0x01;              // Length
    message[5] = 0x09;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (w >> 12) & 0xF;  // w
    message[15] = (w >> 8) & 0xF;   // w
    message[16] = (w >> 4) & 0xF;   // w
    message[17] = (w >> 0) & 0xF;   // w
    message[18] = (h >> 12) & 0xF;  // h
    message[19] = (h >> 8) & 0xF;   // h
    message[20] = (h >> 4) & 0xF;   // h
    message[21] = (h >> 0) & 0xF;   // h
    send(sockfd, message, 22, 0);
}

// draws an oval at the specified location
void GraphicsClient::drawOval(int x, int y, int w, int h) {
    char message[22];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x01;              // Length
    message[4] = 0x01;              // Length
    message[5] = 0x0A;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (w >> 12) & 0xF;  // w
    message[15] = (w >> 8) & 0xF;   // w
    message[16] = (w >> 4) & 0xF;   // w
    message[17] = (w >> 0) & 0xF;   // w
    message[18] = (h >> 12) & 0xF;  // h
    message[19] = (h >> 8) & 0xF;   // h
    message[20] = (h >> 4) & 0xF;   // h
    message[21] = (h >> 0) & 0xF;   // h
    send(sockfd, message, 22, 0);
}

// draws a filled oval at the specified location
void GraphicsClient::fillOval(int x, int y, int w, int h) {
    char message[22];
    message[0] = 0xFF;              // SYNC
    message[1] = 0x00;              // Length
    message[2] = 0x00;              // Length
    message[3] = 0x01;              // Length
    message[4] = 0x01;              // Length
    message[5] = 0x0B;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    message[14] = (w >> 12) & 0xF;  // w
    message[15] = (w >> 8) & 0xF;   // w
    message[16] = (w >> 4) & 0xF;   // w
    message[17] = (w >> 0) & 0xF;   // w
    message[18] = (h >> 12) & 0xF;  // h
    message[19] = (h >> 8) & 0xF;   // h
    message[20] = (h >> 4) & 0xF;   // h
    message[21] = (h >> 0) & 0xF;   // h
    send(sockfd, message, 22, 0);
}

// draws a line starting a point 1 and ending at point 2
void GraphicsClient::drawLine(int x1, int y1, int x2, int y2) {
    char message[22];
    message[0] = 0xFF;               // SYNC
    message[1] = 0x00;               // Length
    message[2] = 0x00;               // Length
    message[3] = 0x01;               // Length
    message[4] = 0x01;               // Length
    message[5] = 0x0D;               // Function
    message[6] = (x1 >> 12) & 0xF;   // x1
    message[7] = (x1 >> 8) & 0xF;    // x1
    message[8] = (x1 >> 4) & 0xF;    // x1
    message[9] = (x1 >> 0) & 0xF;    // x1
    message[10] = (y1 >> 12) & 0xF;  // y1
    message[11] = (y1 >> 8) & 0xF;   // y1
    message[12] = (y1 >> 4) & 0xF;   // y1
    message[13] = (y1 >> 0) & 0xF;   // y1
    message[14] = (x2 >> 12) & 0xF;  // x2
    message[15] = (x2 >> 8) & 0xF;   // x2
    message[16] = (x2 >> 4) & 0xF;   // x2
    message[17] = (x2 >> 0) & 0xF;   // x2
    message[18] = (y2 >> 12) & 0xF;  // y2
    message[19] = (y2 >> 8) & 0xF;   // y2
    message[20] = (y2 >> 4) & 0xF;   // y2
    message[21] = (y2 >> 0) & 0xF;   // y2
    send(sockfd, message, 22, 0);
}

// draws a string of characters on the display
void GraphicsClient::drawString(int x, int y, string str) {
    char message[100];
    message[0] = 0xFF;              // SYNC
    message[5] = 0x05;              // Function
    message[6] = (x >> 12) & 0xF;   // x
    message[7] = (x >> 8) & 0xF;    // x
    message[8] = (x >> 4) & 0xF;    // x
    message[9] = (x >> 0) & 0xF;    // x
    message[10] = (y >> 12) & 0xF;  // y
    message[11] = (y >> 8) & 0xF;   // y
    message[12] = (y >> 4) & 0xF;   // y
    message[13] = (y >> 0) & 0xF;   // y
    int length = 9;
    // add string to message 1 nibble at a time
    for (int i = 0; i < str.length(); i++) {
        message[(2 * i) + 14] = (str.at(i) >> 4) & 0xF;
        message[(2 * i) + 15] = (str.at(i) >> 0) & 0xF;
        length += 2;
    }
    message[1] = (length >> 12) & 0xF;  // Length
    message[2] = (length >> 8) & 0xF;   // Length
    message[3] = (length >> 4) & 0xF;   // Length
    message[4] = (length >> 0) & 0xF;   // Length
    send(sockfd, message, length + 5, 0);
}

// send the redraw (repaint) signal to the attached graphics server
void GraphicsClient::repaint() {
    char message[6];
    message[0] = 0xFF;  // SYNC
    message[1] = 0x00;  // Length
    message[2] = 0x00;  // Length
    message[3] = 0x00;  // Length
    message[4] = 0x01;  // Length
    message[5] = 0x0C;  // Function
    send(sockfd, message, 6, 0);
}

// Request file from server
void GraphicsClient::requestFile() {
    char message[6];
    message[0] = 0xFF;  // SYNC
    message[1] = 0x00;  // Length
    message[2] = 0x00;  // Length
    message[3] = 0x00;  // Length
    message[4] = 0x01;  // Length
    message[5] = 0x0E;  // Function
    send(sockfd, message, 6, 0);
}

// Draws the buttons on the screen to start
void GraphicsClient::drawButtons() {
    int buttonHeight = 35;
    int buttonMargin = 15;
    string labels[11] = {"   Step", "   Run", "  Pause", "  Reset", " Random", "    Load", "     Quit", "Select size:", "   25x25", "   50X50", "   75x75"};
    for (int i = 0; i < 11; i++) {
        if (i != 7) {
            setDrawingColor(100, 100, 100);
            fillRectangle(650 + 3, (i * (buttonHeight + buttonMargin)) + 25 + 3, 100, buttonHeight);
            setDrawingColor(250, 250, 250);
            fillRectangle(650, (i * (buttonHeight + buttonMargin)) + 25, 100, buttonHeight);
        }
        setDrawingColor(0, 0, 0);
        drawString(675, (i * (buttonHeight + buttonMargin)) + 48, labels[i]);
    }
    repaint();
}

// Recieves the messages from the server
Message GraphicsClient::readMessage() {
    char message[100];
    int count;
    ioctl(sockfd, FIONREAD, &count);
    if (count > 20) {
        size_t bytesRead = read(sockfd, message, count);
        Message mObj = Message();
        mObj.parseMessage(message, bytesRead);
        if (mObj.getFunction() == 5) {
            requestFile();
        }
        return mObj;
    }
    return Message();
}
