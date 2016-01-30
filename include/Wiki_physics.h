#include <cmath>
#include "./include/projectile.h"
#include "./include/launcher.h"
//This is a collection of physics based functions, useful in the trajectory simulator
//Constants
const double gravity = 9.81;

double square(double base) {
	double current = base;
		current *= base;
	return current;

}

double ma2f(double mass, double accel) {
	double f = mass * accel;
	return f;
}
double mf2a(double mass, double force) {
	double a = force / mass;
	return a;
}
double fa2m(double force, double accel) {
	double m = force / accel;
	return m;
}

double getDecel(double initVel, double finalVel, double time) {
	double d = (finalVel - initVel) / time;
	return d;

}

double getBallisticDistance(double velocity, double angle, Point startLoc) {
	double distance;
	distance = (((velocity * cos(angle))/ gravity) * (velocity * sin(angle) + (sqrt(square((velocity * sin(angle), 2) + 2*gravity*(startLoc.y))))));
	return distance;
}

double getTimeOfFlight(double distance, double velocity, double angle) {
	double time;
	time = ((distance) / (velocity * cos(angle)));
	return time;

}

double getAngleOfReach(double distance, double velocity) {
	double angle;
	angle = ((1 / 2) * asin((gravity * distance) / square(velocity)));
}

Point getHeightAtX(double x, double velocity, double angle, Point startingLoc) {
	double y;
	y = ((startingLoc.y) + x * tan(angle) - ((gravity * square(x)) / (square(2 * (velocity * cos(angle))))));

}
