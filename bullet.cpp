#include"globals.h"
#include"SFML/Graphics.hpp"
#include"bullet.h"
#include<math.h>


//default constructor
bullet::bullet() {
	xpos = 0;
	ypos = 0;
	alive = true;
}

//destructor
bullet::~bullet() {}

//parameterized constructor with SFML image
bullet::bullet(int x, int y, sf::Sprite sprite, int a) {
	xpos = x;
	ypos = y;
	alive = true;
	image = sprite;
	angle = a;
	radius = 10;
}

//parameterized constructor without imae (not used, code would need to be adjusted)
bullet::bullet(int x, int y, int a) {
	xpos = x;
	ypos = y;
	alive = true;
	angle = a;
	radius = 10;
}

void bullet::move() {
	radius = 20;
	angle -= .1;
	if (angle < -6.28)
		angle = 0;


	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;

}
void bullet::move2() {
	radius = 10;
	angle += .1;
	if (angle > 6.28)
		angle = 0;

	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
}

void bullet::move3() {
	radius = 5;
	angle += .3;
	if (angle > 4.57)
		angle = 0;

	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
}

void bullet::draw(sf::RenderWindow& window) {
	//cout << "position is " << xpos << " , " << ypos;
	sf::CircleShape shape(5);
	shape.setFillColor(sf::Color(100,250, 50));
	if (alive) {
		shape.setPosition(xpos, ypos);
		window.draw(shape);
	}
}

void bullet::kill() {
	alive = false;
}

bool bullet::offScreen() {
	if (ypos < 0)
		return true;
	else if (ypos > 800)
		return true;
	else if (xpos < 0)
		return true;
	else if (xpos > 800)
		return true;
	else
		return false;
}

void bullet::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool bullet::isAlive() {
	return alive;
}

bool bullet::collide(double x, double y) {
	if (sqrt((x - xpos) * (xpos - xpos) + (y - ypos) * (y - ypos)) < 32) {


		return true;
	}
	else
		return false;
}
int bullet::getx() {
	return xpos;
}
int bullet::gety() {
	return ypos;
}


