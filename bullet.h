#pragma once
#include"globals.h"
#include"SFML/Graphics.hpp"

class bullet {
private:
	int xpos;
	int ypos;
	bool alive;
	float angle;
	float radius;
	sf::Sprite image;
public:
	bullet();
	~bullet();
	bullet(int x, int y, sf::Sprite sprite, int a);
	bullet(int x, int y, int a);
	void move();
	void move2();
	void move3();
	void draw(sf::RenderWindow& window);
	void kill();
	bool offScreen();
	void shoot(int x, int y);
	bool isAlive();
	bool collide(double x, double y);
	int getx();
	int gety();
};