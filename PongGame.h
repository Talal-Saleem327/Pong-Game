#pragma once
#include <string>
#include "Button.h"
#include "Ball.h"
#include "Paddle.h"
class PongGame{
	int playerOneScore;
	int playerTwoScore;
	int maxScore;
	Ball* b;
	Paddle* paddleP1, *paddleP2;
	sf::Font f;
	ButtonText* score1Text, *score2Text;

public:
	PongGame(){}

	PongGame(int maxScore) {
		f.loadFromFile("charles-george.regular.ttf");
		playerOneScore = playerTwoScore = 0;

		score1Text = new ButtonText(std::to_string(playerOneScore), sf::Color(61, 61, 61), 50, sf::Vector2f(400, 100), f);
		score2Text = new ButtonText(std::to_string(playerTwoScore), sf::Color(61, 61, 61), 50, sf::Vector2f(830, 100), f);
		this->maxScore = maxScore;
		b = new Ball(610, 330, 30, -2.5, 5);
		paddleP1 = new Paddle(20, 150, 10, 285);
		paddleP2 = new Paddle(20, 150, 1250, 285);
	}

	void moveBall2P() {
		b->move();
	}

	void moveBall1P() {
		b->move(paddleP2);

	}
	void movePaddle1Manually() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			paddleP1->setMovement(0, -20);
			paddleP1->move();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			paddleP1->setMovement(0, 20);
			paddleP1->move();
		}
	}

	void movePaddle2Manually() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			paddleP2->setMovement(0, -20);
			paddleP2->move();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			paddleP2->setMovement(0, 20);
			paddleP2->move();
		}
	}

	int getPlayer1Score() { return playerOneScore; }
	int getPlayer2Score() { return playerTwoScore; }
	int gethigherScore() { return std::max(playerOneScore, playerTwoScore); }

	void draw(sf::RenderWindow& window) {
		score1Text->setString(std::to_string(playerOneScore));
		score2Text->setString(std::to_string(playerTwoScore));
		score1Text->draw(window);
		score2Text->draw(window);
		b->draw(window);
		paddleP1->draw(window);
		paddleP2->draw(window);
	}

	void manageCollisions() {
		b->manageCollision(paddleP1, paddleP2, playerOneScore, playerTwoScore);
	}

	//return 0 if none has won yet, return 1 if player 1 won and 2 if player 2
	int gameWinner() {
		if (b->getPosition().x >= 1220 || playerOneScore == maxScore) 
			return 1;
		if (b->getPosition().x <= 10 || playerTwoScore == maxScore)
			return 2;
		return 0;
	}


};

