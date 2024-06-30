#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ButtonText {
	sf::Text text;
public:
	ButtonText(std::string s, sf::Color color, unsigned int size,sf::Vector2f pos, sf::Font& f) {
		
		text.setFont(f);
		text.setString(s);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(pos.x,pos.y);
	}

	void setString(std::string s) {
		text.setString(s);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(text);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}
};

class Button
{
	ButtonText text;
	sf::RectangleShape* rect;
	sf::Vector2f* position;
	sf::Vector2f* size;
	//sf::Color up, down, hover;
public:
	Button(float sizeX, float sizeY, float posX, float posY, std::string s, sf::Color background, sf::Color textColor, unsigned int textSize, sf::Font& f)
	:text(s, textColor, textSize,sf::Vector2f(posX + 5, posY + 10),f) {
		rect = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
		position = new sf::Vector2f(posX, posY);
		size = new sf::Vector2f(sizeX, sizeY);
		rect->setFillColor(background);
		//rect->setOutlineColor(outline);
		//rect->setOutlineThickness(10);
		rect->setPosition(posX, posY);

	}

	void setBackGroundColor(sf::Color color) {
		rect->setFillColor(color);
	}

	void setTextColor(sf::Color textColor) {
		text.setTextColor(textColor);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(*rect);
		text.draw(window);
	}

	~Button() {
		delete position;
		delete size;
		delete rect;
	}

};

