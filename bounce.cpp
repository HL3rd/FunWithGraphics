// bounce.cpp
// Horacio Lopez, Section 02
// This program is meant to animate a moving circle in a bouncing motion restricted
// by the window.

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gfx.h"
using namespace std;

int main() {
	int wd = 600, ht = 500; // width and height of window
	int dx = 1; // basic increment
	int dy = 1;
	int xc = 100, yc = 100, r = 25; // circle's starting center, and its radius
	char c = 0; // key that user presses
	int deltat = 5000;
	int xm, ym;

	gfx_open(wd, ht, "Window for symbol.cpp"); // opens window
	
	gfx_color(255,255,255); // color of circle will be white
	gfx_circle(xc, yc, r);
	gfx_flush(); // starts the circle

	while (true) {
		xc += dx;
		yc += dy;
		gfx_clear();
		gfx_circle(xc, yc, r); // auto generate a circle in upper left corner
		gfx_flush(); // draws
		usleep(deltat); // pausing
	

		// if circle hits any of the sides
		if (yc <= r)
			dy = (-dy);
		if (yc >= ht - r)
			dy = (-dy);
		if (xc <= r)
			dx = (-dx);
		if (xc >= wd - r)
			dx = (-dx);
		
		// if user enter presses a key
		if (gfx_event_waiting() == true) {
			c = gfx_wait();	// c is the key that is pressed
			// if the user clicked, execute below
			if (c == 1) {
				gfx_clear();
				xm = gfx_xpos();
				ym = gfx_ypos();
				xc = xm;
				yc = ym;
				srand (time(NULL));
				deltat = rand() % 10000 + 2500;
				gfx_circle(xc, yc, r);
				usleep(deltat); // pausing and display speed is now random
			}
		}

		if (c == 'q')
			break; // quit when 'q' is pressed

	}

	return 0;
}

