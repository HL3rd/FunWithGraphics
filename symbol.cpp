// symbol.cpp
//Horacio Lopez, Section 02
// This program will display various polygons according to keys pressed by the user.

#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>

#include "gfx.h"
using namespace std;

void printPoly(char, int, int);

int main() {
	int wd = 600, ht = 500; // window width and height
	char c = 0; // key char that is pressedi
	int xm, ym, rad; // mouse click coordinates

	gfx_open(wd, ht, "Window for symbol.cpp"); // open a window to begin shapes

	while (true) {
		c =  gfx_wait(); // calls the key that the user hit
		xm = gfx_xpos(); // get mouse's x coordinate
		ym = gfx_ypos(); // get mouse's y coordinate

		switch (c) {
			
			// following will print a blue square around the user's mouse click
			case 1:
				gfx_color(0, 0, 255);
				printPoly('4', xm, ym);
				/*gfx_line(xm - 12, ym - 12, xm - 12, ym + 12);
				gfx_line(xm - 12, ym + 12, xm + 12, ym + 12);
				gfx_line(xm + 12, ym + 12, xm + 12, ym - 12);
				gfx_line(xm + 12, ym - 12, xm - 12, ym - 12);*/
				break;

			// following will print a green triangle when 't' is pressed
			case 't':
				gfx_color(0, 255, 0);
				printPoly('3', xm, ym);	
				break;

			// following will print a white circle when c is pressed
			case 'c':
				rad = 25; // radius for circle
				gfx_color(255, 255, 255);
				gfx_circle(xm, ym, rad);
				break;

			// following will allow the printing of polygons of respective side #
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				gfx_color(255,0,255);
				printPoly(c, xm, ym);
				break;
			
			// following will clear board when 'esc' is pressed
			case 27:
				gfx_clear();
				break;

			case 'q':
				return 0;
				break; // quit when 'q' is pressed

			default:
				break;
		}
	}

	return 0;
}

// this function will print polygons of any number of sides from 3 to 9
void printPoly(char c, int xm, int ym) {
	double pi = 3.14159;
	int i = c - '0'; // converts c into an int

	int sideLength = 25;
	double theta = 0.0; // starting angle
	double theta_i = (2*pi)/i; // increment
	double r = (sideLength)/(2*sin(180/sideLength)); // radius depending on sides	
	
	// starting at theta = 0, and x = r for polar coordingates
	double x0 = xm + r;
	double y0 = ym;
	// at every increment add (2pi)/sides to theta
	for(int j = 0; j < i; j++) {
		theta =  theta + theta_i;
		double xi = xm + r*cos(theta);
		double yi = ym + r*sin(theta);
		gfx_line(x0, y0, xi, yi);

		x0 = xi;
		y0 = yi;
	}

}
