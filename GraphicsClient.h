#pragma once

#include <string>

#include "Message.h"
using namespace std;

/**
 * Client to interact with GraphicsServer.jar
 */
class GraphicsClient {
   public:
    /**
     * GC constructor
     * @param url url of the GraphicsServer to connect to
     * @param port port of the GraphicsServer to connect to
     */
    GraphicsClient(string url, int port);

    /**
     * GC copy constructor
     * @param origGraphicsClient original GC to be copied
     */
    GraphicsClient(const GraphicsClient& origGraphicsClient);

    /**
     * GC deconstructor
     */
    ~GraphicsClient();

    /**
     * GC operator= method
     * @param objToCopy the rhs object to copy
     * @param
     */
    GraphicsClient& operator=(const GraphicsClient& objToCopy);

    /**
     * sets the background color of the associated display
     * @param r value of red
     * @param g value of green
     * @param b value of blue
     */
    void setBackgroundColor(int r, int g, int b);

    /**
     * set the color that objects will be drawn at until another setDrawingColor call is made.
     * @param r value of red
     * @param g value of green
     * @param b value of blue
     */
    void setDrawingColor(int r, int g, int b);

    /**
     * clears the display to the background color
     */
    void clear();

    /**
     * sets the pixel at the location to the color
     * @param x x position on GS
     * @param y y position on GS
     * @param r value of red
     * @param g value of green
     * @param b value of blue
     */
    void setPixel(int x, int y, int r, int g, int b);

    /**
     * draws a rectangle at the specified coordinates to the color
     * @param x x position on GS
     * @param y y position on GS
     * @param w width of shape
     * @param h height of shape
     */
    void drawRectangle(int x, int y, int w, int h);

    /**
     * draws a filled rectangle at the position 
     * @param x x position on GS
     * @param y y position on GS
     * @param w width of shape
     * @param h height of shape
     */
    void fillRectangle(int x, int y, int w, int h);

    /**
     * clears (sets the pixels to the background color) at the location and size
     * @param x x position on GS
     * @param y y position on GS
     * @param w width of shape
     * @param h height of shape
     */
    void clearRectangle(int x, int y, int w, int h);

    /**
     * draws an oval at the specified location 
     * @param x x position on GS
     * @param y y position on GS
     * @param w width of shape
     * @param h height of shape
     */
    void drawOval(int x, int y, int w, int h);

    /**
     * draws a filled oval at the specified location 
     * @param x x position on GS
     * @param y y position on GS
     * @param w width of shape
     * @param h height of shape
     */
    void fillOval(int x, int y, int w, int h);

    /**
     * draws a line starting a point 1 and ending at point 2
     * @param x1 x1 position of line
     * @param y1 y1 position of line
     * @param x2 x2 position of line
     * @param y2 y2 position of line
     */
    void drawLine(int x1, int y1, int x2, int y2);

    /**
     * draws a string of characters on the display
     * @param x x position on GS
     * @param y y position on GS
     * @param str string to be drawn on screen
     */
    void drawString(int x, int y, string str);

    /**
     * send the redraw (repaint) signal to the attached graphics server
     */
    void repaint();

    /**
     * Request file from server
     */
    void requestFile();

    /**
     * Recieves the messages from the server
     * @return Message message object containg the message info
     */
    Message readMessage();

    /**
     * Draws the buttons on the screen to start
     */
    void drawButtons();

   private:
    /**
     * url of the GraphicsServer to connect to
     */
    string url;

    /**
     * port of the GraphicsServer to connect to
     */
    int port;

    /**
     * socket of the GraphicsServer to connect to
     */
    int sockfd;
};
