#pragma once

#include <string>
using namespace std;

class Message {
   public:
    /**
     * default constructor
     */
    Message();

    /**
     * draws a string of characters on the display
     * @param f function of message
     * @param m message itself
     */
    Message(int f, string m);

    /**
     * return function
     */
    int getFunction();

    /**
     * set function
	 * @param f function
     */
    void setFunction(int f);

    /**
     * return message
     */
    string getMessage();

    /**
     * set message
	 * @param m message
     */
    void setMessage(string m);

    /**
     * Parses raw message to get function and file path
     * @param m raw message
     * @param length length of message in bytes
     */
    void parseMessage(char* m, int length);

    /**
     * Return function number based of position of mouse click
     * @param x x position of mouse
     * @param y y position of mouse
     */
    int decideFunction(int x, int y);

    /**
     * return mouse y position
     */
    int getMouseY();

    /**
     * set mouse y position
	 * @param y y position of mouse
     */
    void setMouseY(int y);

    /**
     * returns mouse x position
     */
    int getMouseX();

    /**
     * set mouse x position
	 * @param x x position of mouse
     */
    void setMouseX(int x);

   private:
    /**
     * function as an integer
     */
    int function;

    /**
     * mouse x position
     */
    int mouseX;

    /**
     * mouse y position
     */
    int mouseY;

    /**
     * message / file path
     */
    string message;
};
