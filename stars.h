#pragma once
class stars {
private:
	int xpos;
	int ypos;
	int RG;
	int blue;
	int size;
	sf::Sprite image;
public:
	stars();
	~stars();
	void move();
	void reposition();
	void draw(sf::RenderWindow& window);
	
};