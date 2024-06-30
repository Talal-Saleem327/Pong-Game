#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PongGame.h"
#include "Menu.h"
#include "Source.h"
#include "HighScoreWindow.h"

#define MAX_SCORE 10
using namespace std;
using namespace sf;

int main()
{
    GameState state = MENU;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong Game");
    sf::Vector2f mouseCLickPosition(-1, -1);
    PongGame* game=new PongGame(MAX_SCORE);
    HighScoreWindow h;
    Image bgImage;
    bgImage.loadFromFile("./background.png");
    Texture backGroundTexture;
    backGroundTexture.loadFromImage(bgImage);
    Sprite bg;
    bg.setTexture(backGroundTexture);

    sf::Image iconImage = sf::Image{};
    iconImage.loadFromFile("icon.png");
    window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

    Menu gameMenu(&window);
    bool mouseClicked = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouseCLickPosition.x = event.mouseButton.x;
                mouseCLickPosition.y = event.mouseButton.y;
                mouseClicked = true;
                cout << "Pressed: (" << mouseCLickPosition.x << " , " << mouseCLickPosition.y << ")\n";
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (state == IN_GAME_1P || state == IN_GAME_2P) {
                    game->movePaddle1Manually();
                    if (state == IN_GAME_2P)
                        game->movePaddle2Manually();
                }
                
            }
        }
        window.clear();
        window.draw(bg);
        if (state == MENU) {
            if (game == nullptr) {
                game = new PongGame(MAX_SCORE);
            }
            gameMenu.draw();
            gameMenu.handleHoverEvent();
            if (mouseClicked) {
                gameMenu.handleMouseEvent(mouseCLickPosition, state);
                mouseClicked = false;
            }
        }
        else if (state == IN_GAME_2P) {
            game->manageCollisions();
            game->moveBall2P();
            game->draw(window);
            int winner = game->gameWinner();
            if (winner != 0) {

                state = MENU;
                gameMenu.setWinner(winner);
                h.addHighScore(game->gethigherScore());
                delete game;
                game = nullptr;
                gameMenu.startMusic();
            }
        }

        else if (state == IN_GAME_1P) {
            game->manageCollisions();
            game->moveBall1P();
            game->draw(window);
            int winner = game->gameWinner();
            if (winner != 0) {
                state = MENU;
                gameMenu.setWinnervsCPU(winner);
                h.addHighScore(game->getPlayer1Score());
                delete game;
                game = nullptr;
                gameMenu.startMusic();
            }

        }
        else if (state == HIGH_SCORE) {
            h.draw(window);
            h.handleHoverEvent(window);
            if (mouseClicked) {
                h.handleMouseEvent(mouseCLickPosition, state);
                mouseClicked = false;
            }
        }
        
        window.display();


    }


    delete game;
    return 0;
}