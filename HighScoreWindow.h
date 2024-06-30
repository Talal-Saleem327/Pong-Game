#pragma once
#include <algorithm>
#include <fstream>
#include "Button.h"
#include "Menu.h"

class HighScoreWindow {
	Button* back;
	ButtonText** highScores;
	int* highScoresArr;
	int highScoreCount;
	sf::Font f;


public:
	HighScoreWindow() {

		int count;
		std::ifstream file("highScores.txt", std::ios::in);
		file >> highScoreCount;
		highScoresArr = new int[highScoreCount + 1];
		std::cout << "High Scores:\n";
		for (int i = 0; i < highScoreCount; i++) {
			file >> highScoresArr[i];
			std::cout << highScoresArr[i] << std::endl;
		}
		file.close();
		f.loadFromFile("tokeely-brookings.regular.ttf");

		back = new Button(100, 50, 10, 10, std::string("BACK"), sf::Color::Transparent, sf::Color::Blue, 40, f);
		highScores = new ButtonText * [highScoreCount + 1];
		highScores[0] = new ButtonText("HIGH SCORES", sf::Color::White, 70, sf::Vector2f(300, 50), f);
		for (int i = 1; i <= highScoreCount; i++) {
			highScores[i] = new ButtonText(std::to_string(highScoresArr[i - 1]), sf::Color::White, 50, sf::Vector2f(400, 80 + (i * 70)), f);

		}

	}

	void addHighScore(int score) {
		bool found = false;
		for (int i = 0; i < highScoreCount; i++) {
			if (highScoresArr[i] == score) {
				found = true;
				break;
			}
		}

		if (!found) {
			highScoresArr[highScoreCount] = score;
			std::sort(highScoresArr, highScoresArr + highScoreCount + 1, std::greater<int>());
			std::ofstream file("highScores.txt");
			file << highScoreCount << std::endl;

			std::cout << "High scores:\n";
			for (int i = 0; i < highScoreCount; i++) {
				file << highScoresArr[i] << std::endl;
				highScores[i + 1]->setString(std::to_string(highScoresArr[i]));
				std::cout << highScoresArr[i] << std::endl;
			}

			/*for (int i = 1; i <= highScoreCount; i++) {
				highScores[i]->setString(std::to_string(highScoresArr[i]));
			}*/
		}
	}

	bool handleMouseEvent(sf::Vector2f& mouseCLickPosition, GameState& state) {
		if ((mouseCLickPosition.x >= 10 && mouseCLickPosition.x <= 110) &&
			(mouseCLickPosition.y >= 10 && mouseCLickPosition.y <= 60)) {
			state = MENU;
			return true;
		}
		return false;
	}
	void handleHoverEvent(sf::RenderWindow& window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if ((mousePosition.x >= 10 && mousePosition.x <= 120) && 
			(mousePosition.y >= 10 && mousePosition.y <= 60))
			back->setTextColor(sf::Color::Red);
		else
			back->setTextColor(sf::Color::Blue);

	}


	void draw(sf::RenderWindow& window) {
		for (int i = 0; i <= highScoreCount; i++)
			highScores[i]->draw(window);

		back->draw(window);
	}
	~HighScoreWindow() {
		delete back;

		for (int i = 0; i <= highScoreCount; i++)
			delete highScores[i];
		delete [] highScores;

		delete []highScoresArr;
	}
};

