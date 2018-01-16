// animate.cpp
// Horacio Lopez, Section 02
// This program will print a slider that is controlled by the user using the 'a' and 'd'
// keys. The user can control the speed and size of the spinning circle.

// The goal of this was to setup for my final project. Please ignore commented out code at bottom

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gfx.h"
using namespace std;

void bottomHalf(float xc, float yc, float r, int deltat, float theta, float rot_r);
void topHalf(float xc, float yc, float r, int deltat, float theta, float rot_r);
void printTriangle(float, float &, int, int);
// bool shoot(float, float, float, float, int, int);

int main() {
	int wd = 500, ht = 600; // width and height of window
	char c = 0; // will be the keys pressed by the user	
	gfx_open(wd, ht, "Window for animate.cpp");

	// following generates random colors for the shapes
	int red, green, blue;
	
	// start at purple
	red = 162;
	green = 0;
	blue = 255;

	gfx_color(red, green, blue);
	
	// setting the size and start of moving shape
	float xc = 200.0; // starting x-coord
	float yc = 300.0; // starting y-coord
	float r = 50; // staring radius of circle

	float pi = 3.14159;
	float theta = 0.0;
	float theta_i = pi / 1000;

	// generate rotating circle
	gfx_circle(xc, yc, r);

	//create circle outlines that map movement
	gfx_flush(); // starts the circles

	float rot_r = 25.0;
	int deltat = 5000;
		
	float x0 = 0; // starting position of triangle
	float movement = 10;

	while(true) {
		// following rotates the circle		
		if (theta >= 0.0 && theta < pi)
			topHalf(xc, yc, r, deltat, theta, rot_r);
		if (theta >= pi && theta <= 2*pi)
			bottomHalf(xc, yc, r, deltat, theta, rot_r);

		// following prints the triangle and controls movement and appearance
		printTriangle(movement, x0, wd, ht);
		if (gfx_event_waiting() == true) {
			c = gfx_wait();
			if (c == 'd') {
				x0 += movement;
				printTriangle(movement, x0, wd, ht);

				// colors get warmer
				if (red < 250)
					red += 5;
				if (green < 250)
					green += 10;

				// makes spinning faster
				if (deltat > 1000)
					deltat -= 100;

				if (r > 12)
					r -= 1;  // makes radius of circle smaller

				gfx_color(red, green, blue);

			} else if (c == 'a') {
				x0 -= movement;
				printTriangle(movement, x0, wd, ht);

				// colors get colder
				if (red > 172)
					red = red -10;
				if (green > 5)
					green = green - 5;
				
				// makes spinning slower
				if (deltat < 5000)
					deltat += 100;	

				if (r <= 50)
					r += 1; // makes radius of circle bigger

				gfx_color(red, green, blue);

			} else if (c == 32) {
				// shoot(x0, r, xc, yc, wd, ht); // if the user shoots

			} else if (c == 'q') {
				break;
			}

		}

		theta += theta_i; // incrementing the rotating circle path
		
		if (theta > (2 * pi)) {
			theta = 0.0;
		}
	
		
	}

	return 0;
	
}

void bottomHalf(float xc, float yc, float r, int deltat, float theta, float rot_r) {
	float pi = 3.14159;

	if (theta >= pi && theta < (3*pi)/2) {
		xc += sqrt(pow(rot_r, 2) - pow(rot_r * cos(theta), 2));
		yc += sqrt(pow(rot_r, 2) - pow(rot_r * sin(theta), 2));
		gfx_clear();
		gfx_circle(xc, yc, r);
		gfx_flush(); // draws
		usleep(deltat); // pausing
	} else if (theta >= (3*pi)/2 && theta < 2*pi) {
		xc += sqrt(pow(rot_r, 2) - pow(rot_r * cos(theta), 2));
		yc -= sqrt(pow(rot_r, 2) - pow(rot_r * sin(theta), 2));
		gfx_clear();
		gfx_circle(xc, yc, r);
		gfx_flush(); // draws
		usleep(deltat); // pausing
	}

}

void topHalf(float xc, float yc, float r, int deltat, float theta, float rot_r) {
	float pi = 3.14159;

	if (theta >= 0.0 && theta < pi/2) {
		xc -= sqrt(pow(rot_r, 2) - pow(rot_r * cos(theta), 2));
		yc -= sqrt(pow(rot_r, 2) - pow(rot_r * sin(theta), 2));
		gfx_clear();
		gfx_circle(xc, yc, r);
		gfx_flush(); // draws
		usleep(deltat); // pausing
	} else if (theta >= pi/2 && theta < pi) {
		xc -= sqrt(pow(rot_r, 2) - pow(rot_r * cos(theta), 2));
		yc += sqrt(pow(rot_r, 2) - pow(rot_r * sin(theta), 2));
		gfx_clear();
		gfx_circle(xc, yc, r);
		gfx_flush(); // draws
		usleep(deltat); // pausing
	}

}

void printTriangle(float movement, float& x0, int wd, int ht) {
	float x2, x3;
	x2 = x0 + 26; // right-most point
	x3 = (x0 + x2) / 2; // mid and top point

	if (x0 >= 0 && x2 <= wd) {
		gfx_line(x0, ht-5, x2, ht-5);
		gfx_line(x2, ht-5, x3, ht-25);
		gfx_line(x3, ht-25, x0, ht-5);
	// if user is moving out of the left bound
	} else if (x0 < 0) {
		x0 = 0.0;
		x2 = x0 + 26;
		x3 = (x0 + x2) / 2;
		gfx_line(x0, ht-5, x2, ht-5);
		gfx_line(x2, ht-5, x3, ht-25);
		gfx_line(x3, ht-25, x0, ht-5);
	// if user is moving out of the right bound
	} else if (x2 > wd) {
		x0 = wd - 26;
		x2 = x0 + 26;
		x3 = (x0 + x2) / 2;
		gfx_line(x0, ht-5, x2, ht-5);
		gfx_line(x2, ht-5, x3, ht-25);
		gfx_line(x3, ht-25, x0, ht-5);
	}

}

/*
bool shoot(float x0, float r, float xc, float yc, int wd, int ht ) {
	bool hit = false;
	float x2, x3;
	x2 = x0 + 26;
	x3 = (x0 + x2) / 2;
	float y0 = ht-25; // start of bullet
	float yi = ht-30; // end of bullet
	
	while (yi != ht) {
		gfx_line(x3, y0, x3, yi);

		// if equal to position of circle
		if (yi == yc + r && x3 == xc + r) {
			hit = true;
			gfx_color(255, 0, 0);
			gfx_circle(wd-20, ht+20, 10);
			return hit;
		}

		y0 += 5; // moving up
		yi += 5;
	}

}
*/
