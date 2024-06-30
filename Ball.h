#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.h"


class Ball{
	sf::CircleShape* circle;
	sf::Vector2f* position;
	sf::Vector2f* speed;
	float radius;
	sf::Clock clock;
	sf::SoundBuffer buf;
	sf::Sound bumpMusic;

public:
	Ball() {
		circle = new sf::CircleShape(30, 150);
		circle->setFillColor(sf::Color::Red);
		circle->setPosition(0,0);
		position = new sf::Vector2f(0, 0);
		speed = new sf::Vector2f(0, 0);
		this->radius = radius;

	}

	Ball(float posX, float posY, float radius, float speedX, float speedY) {
		circle = new sf::CircleShape(radius,150);
		circle->setFillColor(sf::Color::Red);
		circle->setPosition(posX, posY);
		position = new sf::Vector2f(posX, posY);
		speed = new sf::Vector2f(speedX, speedY);
		this->radius = radius;
		if (!buf.loadFromFile("bump.wav"))
			std::cout << "Error loading music\n";
		bumpMusic.setBuffer(buf);
	}

	Ball(const Ball& obj) {
		position = new sf::Vector2f(obj.position->x, obj.position->y);
		speed = new sf::Vector2f(obj.speed->x,obj.speed->y);
		this->radius = obj.radius;
	}

	sf::Vector2f getPosition() {
		return *position;
	}

	sf::Vector2f getVelocity() { 
		return *speed;
	}

	float getRadius() {
		return radius;
	}

	void setPosition(float x, float y) {
		position->x = x;
		position->y = y;
		circle->setPosition(x, y);
	}

	void setVelocity(float x, float y) {
		speed->x = x;
		speed->y = y;
	}

	void manageCollision(Paddle* p1, Paddle* p2, int& score1, int& score2) {
		if (position->x >= 1190 && ((position->y + radius >= p2->getPosition().y) && (position->y + radius <= p2->getPosition().y + p2->getSize().y))) {
			position->x = 1189;
			circle->setPosition(sf::Vector2f(position->x, position->y));
			speed->x = -speed->x;
			bumpMusic.setPlayingOffset(sf::seconds(0.f));
			bumpMusic.play();
			score2++;
		}
		
		if (position->x <= 30 && ((position->y + radius >= p1->getPosition().y) && (position->y + radius <= p1->getPosition().y + p1->getSize().y))) {
			position->x = 31;
			circle->setPosition(sf::Vector2f(position->x, position->y));
			speed->x = -speed->x;
			bumpMusic.setPlayingOffset(sf::seconds(0.f));
			bumpMusic.play();
			score1++;
		}
		
	}

	void move() {
		sf::Time elapsed2 = clock.getElapsedTime();
		if (elapsed2.asSeconds() > 0.01) {
			if (position->y >= 710 - 2*(radius) || position->y <= 10) {
				speed->y = -speed->y;
				bumpMusic.setPlayingOffset(sf::seconds(0.f));
				bumpMusic.play();
			}

			circle->move(speed->x, speed->y);
			position->x += speed->x;
			position->y += speed->y;
			clock.restart();
		}
	}

	void move(Paddle*& p) {
		sf::Time elapsed2 = clock.getElapsedTime();
		if (elapsed2.asSeconds() > 0.01) {
			if (position->y >= 710 - 2 * (radius) || position->y <= 10) {
				speed->y = -speed->y;
			}
			circle->move(speed->x, speed->y);
			position->x += speed->x;
			position->y += speed->y;
			clock.restart();

			p->setMovement(0, speed->y);
			p->move();
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(*circle);
	}


	~Ball() {
		delete position;
		delete speed;
	}
};

