#pragma once
#include <SFML/Audio.hpp>
#include "Button.h"

enum GameState { 
	MENU, 
	IN_GAME_1P,
	IN_GAME_2P,
	HIGH_SCORE
};

class Menu
{
	Button* startGameVSPlayerButton;
	Button* highScoresButton;
	Button* startGameVSComputerButton;
	Button* exitButton;
	sf::RenderWindow* window;
	sf::Font f;
	ButtonText* winnerText;
	bool winner;
	sf::SoundBuffer buf;
	sf::Sound mainMenuMusic;

public:
	Menu(sf::RenderWindow* window) {
		winner = false;
		this->window = window;
		std::string winnerStr = "No winner yet";
		std::string playStr1 = "PLAY VS ANOTHER PLAYER";
		std::string playStr2 = "PLAY VS CPU";
		std::string playStr3 = "HIGH SCORES";
		std::string playStr4 = "QUIT";

		f.loadFromFile("PartyConfetti.ttf");
		winnerText = new ButtonText(winnerStr, sf::Color::Red, 50, sf::Vector2f(700, 300), f);
		startGameVSPlayerButton = new Button(450, 80, 150, 50, playStr1, sf::Color(156, 156, 156, 70), sf::Color::Blue, 40, f);
		startGameVSComputerButton = new Button(450, 80, 150, 200, playStr2, sf::Color(156, 156, 156, 70), sf::Color::Blue, 40, f);
		highScoresButton = new Button(450, 80, 150, 350, playStr3, sf::Color(156, 156, 156, 70), sf::Color::Blue, 40, f);
		exitButton = new Button(450, 80, 150, 500, playStr4, sf::Color(156, 156, 156, 70), sf::Color::Blue, 40, f);

		if (!buf.loadFromFile("mainMenu.wav"))
			std::cout << "Error loading music\n";
		mainMenuMusic.setBuffer(buf);
		mainMenuMusic.play();
	}

	void draw() {
		if (winner) {
			winnerText->draw(*window);
		}
		startGameVSPlayerButton->draw(*window);
		highScoresButton->draw(*window);
		startGameVSComputerButton->draw(*window);
		exitButton->draw(*window);

	}
	bool handleMouseEvent(sf::Vector2f& mouseCLickPosition, GameState& state) {
		

		if (mouseCLickPosition.x >= 150 && mouseCLickPosition.x <= 600) {
			if (mouseCLickPosition.y >= 50 && mouseCLickPosition.y <= 199) {
				mainMenuMusic.pause();
				mainMenuMusic.setPlayingOffset(sf::seconds(0.f));
				state = IN_GAME_2P;
				resetWinner();
				return true;
			}
			else if (mouseCLickPosition.y >= 200 && mouseCLickPosition.y <= 349) {
				mainMenuMusic.pause();
				mainMenuMusic.setPlayingOffset(sf::seconds(0.f));
				state = IN_GAME_1P;
				resetWinner();
				return true;
			}
			else if (mouseCLickPosition.y >= 350 && mouseCLickPosition.y <= 499) {
				state = HIGH_SCORE;
				return true;
			}
			else if (mouseCLickPosition.y >= 500 && mouseCLickPosition.y <= 650) {
				window->close();
				return true;
			}
		}
		return false;
	}

	void handleHoverEvent() {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		if (mousePosition.x >= 150 && mousePosition.x <= 600) {
			if (mousePosition.y >= 50 && mousePosition.y <= 199)
				startGameVSPlayerButton->setTextColor(sf::Color::Red);
			else
				startGameVSPlayerButton->setTextColor(sf::Color::Blue);

			if (mousePosition.y >= 200 && mousePosition.y <= 349)
				startGameVSComputerButton->setTextColor(sf::Color::Red);
			else
				startGameVSComputerButton->setTextColor(sf::Color::Blue);

			if (mousePosition.y >= 350 && mousePosition.y <= 499)
				highScoresButton->setTextColor(sf::Color::Red);
			else
				highScoresButton->setTextColor(sf::Color::Blue);

			if (mousePosition.y >= 500 && mousePosition.y <= 650)
				exitButton->setTextColor(sf::Color::Red);
			else
				exitButton->setTextColor(sf::Color::Blue);
		}
	}

	void setWinner(int player) {
		if (player == 1) {
			std::string s = "PLAYER 1 IS THE WINNER";
			winnerText->setString(s);
			winner = true;
		}
		else if (player == 2) {
			std::string s = "PLAYER 2 IS THE WINNER";
			winnerText->setString(s);
			winner = true;
		}
	}

	void resetWinner() {
		winner = false;
	}

	void setWinnervsCPU(int player) {
		if (player == 1) {
			std::string s = "YOU WON";
			winnerText->setString(s);
			winner = true;
		}
		else if (player == 2) {
			std::string s = "YOU LOSE";
			winnerText->setString(s);
			winner = true;
		}
	}

	void startMusic() {
		mainMenuMusic.play();
	}
	~Menu() {
		
		delete startGameVSPlayerButton;
		delete highScoresButton;
		delete startGameVSComputerButton;
		delete exitButton;
	}
};

