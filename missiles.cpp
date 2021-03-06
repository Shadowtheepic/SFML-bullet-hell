#include"globals.h"
#include"SFML/Graphics.hpp"
#include"missiles.h"
#include<math.h>


//default constructor
missile::missile() {
	xpos = 0;
	ypos = 0;
	alive = false;
}

//destructor
missile::~missile() {}

//parameterized constructor with SFML image
missile::missile(int x, int y, sf::Sprite sprite) {
	xpos = x;
	ypos = y;
	alive = false;
	image = sprite;
}

//parameterized constructor without imae (not used, code would need to be adjusted)
missile::missile(int x, int y) {
	xpos = x;
	ypos = y;
	alive = false;
}

void missile::move() {
	ypos -= 5;//simply move up the missile when called
}

void missile::draw(sf::RenderWindow& window) {
	if (alive) {
		image.setPosition(xpos, ypos);
		window.draw(image);
	}
}

void missile::kill() {
	alive = false;
}

bool missile::offScreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}

void missile::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool missile::isAlive() {
	return alive;
}

bool missile::collide(double x, double y) {
	if (sqrt((x - xpos) * (xpos - xpos) + (y - ypos) * (y - ypos)) < 32) {


		return true;
	}
	else
		return false;
}
int missile::getx() {
	return xpos;
}
int missile::gety() {
	return ypos;
}