#include "projectile.h"
//Point operators

//End operators
Projectile::Projectile(Point location, double angle) {
	this->startLoc = location;
	this->initAngle = angle;
}


Projectile::~Projectile() {
}

void Projectile::setVelocity(double v) {
	velocity = v;
}

void Projectile::setMass(double m) {
	mass = m;
}

void Projectile::updateCurrentLoc(Point newLoc) {
	this->currentLoc = newLoc;
}

//Getters
double Projectile::getVelocity() {
	return this->velocity;
}

double Projectile::getMass() {
	return this->mass;
}

double Projectile::getInitialAngle() {
	return this->initAngle;
}

Point Projectile::getCurrentLoc() {
	return this->currentLoc;
}

Point Projectile::getStartLoc() {
	return this->startLoc;
}