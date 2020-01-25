#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
	Display *d;
  	Window w;
  	int s;
  	GC gc;
  	unsigned long colours[19];
  	int width, height;

 	public:
 	 Xwindow(int width=480, int height=570);  // Constructor; displays the window.
  	~Xwindow();                              // Destructor; destroys the window.
  //	Xwindow(const Xwindow&) = delete;
  	Xwindow &operator=(const Xwindow&) = delete;

	enum { // Available colours
		Black=0, White, Red, 
		Green, Blue, Cyan, 
		Yellow, Magenta, Orange, 
		Brown, PapayaWhip, Tomato,
        DarkOrange, Teal, YellowGreen,
        Purple, CadetBlue, DarkSlateGray,
        Grey19
	};

  	// Draws a rectangle
  	void fillRectangle(int x, int y, int width, int height, int colour=Black);

  	// Draws a string
  	void drawString(int x, int y, std::string msg, int colour=Black);

  	// Draws a string
  	void drawBigString(int x, int y, std::string msg, int colour=Black);

  	// Prints the first 10000 available fonts
  	void showAvailableFonts();
};

#endif
