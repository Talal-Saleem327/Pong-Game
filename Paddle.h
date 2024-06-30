#pragma once
#include <SFML/Graphics.hpp>
class Paddle{
	sf::RectangleShape* rect;
	sf::Vector2f* position;
	sf::Vector2f* size;
	sf::Vector2f* movement;
public:
	Paddle(){}

	Paddle(float sizeX, float sizeY, float posX, float posY) {
		rect = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
		movement = new sf::Vector2f(0, 10);
		position = new sf::Vector2f(posX, posY);
		size = new sf::Vector2f(sizeX, sizeY);
		rect->setFillColor(sf::Color::White);
		rect->setOutlineColor(sf::Color::White);
		rect->setOutlineThickness(0.25);
		rect->setPosition(posX, posY);
	}

	sf::Vector2f getPosition() {
		return *position;
	}

	void setPosition(float x, float y) {
		position->x = x;
		position->y = y;
	}

	sf::Vector2f getMovement() {
		return *movement;
	}

	void setMovement(float x, float y) {
		movement->x = x;
		movement->y = y;
	}

	sf::Vector2f getSize() {
		return *size;
	}

	void move() {
		if ((position->y + movement->y) >= 10 && (position->y + movement->y) <= (710 - size->y)) {
			position->y += movement->y;
			rect->move(0, movement->y);
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(*rect);
	}

	~Paddle() {
		delete rect;
		delete position;
		delete size;
		delete movement;
	}
};

