#include"globals.h"
#include"SFML/Graphics.hpp"
#include"stars.h"
#include<math.h>
#include<random>


//default constructor
stars::stars() {
	xpos = rand() % 800+1;
	ypos = rand() % 600 +1;
	RG = rand() % 200;
	blue = rand() % 150 + 100;
	size = rand()% 1 + 1;
}

//destructor
stars::~stars() {}



void stars::move() {
	ypos += 10;

}

void stars::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(5);
	shape.setFillColor(sf::Color(RG, RG, blue));
	shape.setPosition(xpos, ypos);
	window.draw(shape);
}

void stars::reposition() {
	if (ypos > 800) {
		ypos = 0;
		xpos = rand() % 800 + 1;
		RG = rand() % 200;
		blue = rand() % 150 + 100;
	}
}
