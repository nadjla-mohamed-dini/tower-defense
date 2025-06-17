#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <optional>
#include "Menu.h"
#include "GameState.hpp"
#include "HUD.hpp"
#include <iostream>
#include "GameScene.hpp"
#include "ScoreScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Menu du jeu");

    sf::Font police;
    if (!police.openFromFile("font.ttf")) {
        std::cerr << "Error for changing the police\n";
        return EXIT_FAILURE;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/background_menu.jpg")) {
        std::cerr << "Error for charging the background\n";
        return EXIT_FAILURE;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    sf::Vector2f scale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    backgroundSprite.setScale(scale);

    Menu menu(window.getSize().x, window.getSize().y, police);
    ScoreScreen scoreScreen(police);  // <-- pas besoin de loadScores ici

    HUD hud(police);
    sf::Clock gameClock;
    sf::Clock deltaClock;

    enum class Screen { Menu, Map, Scores };
    Screen currentScreen = Screen::Menu;

    GameState gameState;
    GameScene gameScene(window, &gameState);
    gameState.registerObserver(&hud);
    gameScene.loadAssets();
    gameScene.spawnEnemies();

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("images/field1.png")) {
        std::cerr << "Error for charging the map\n";
        return EXIT_FAILURE;
    }
    sf::Sprite mapSprite(mapTexture);

    // Adjust the map for the window
    sf::Vector2u mapSize = mapTexture.getSize();
    sf::Vector2f mapScale(
        static_cast<float>(windowSize.x) / mapSize.x,
        static_cast<float>(windowSize.y) / mapSize.y
    );
    mapSprite.setScale(mapScale);



    while (window.isOpen()) {
        while (auto evenement = window.pollEvent()) {
            if (evenement->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (evenement->is<sf::Event::KeyPressed>()) {
                auto touch = evenement->getIf<sf::Event::KeyPressed>();
                if (touch) {
                    if (currentScreen == Screen::Menu) {
                        if (touch->code == sf::Keyboard::Key::Up) {
                            menu.monter();
                        }
                        else if (touch->code == sf::Keyboard::Key::Down) {
                            menu.descendre();
                        }
                        else if (touch->code == sf::Keyboard::Key::Enter) {
                            int choice = menu.getIndexSelectionne();
                            if (choice == 0) {
                                currentScreen = Screen::Map;
                                gameClock.restart();
                                deltaClock.restart();
                            }
                            else if (choice == 2) {
                                window.close();
                            }
                            else if (choice == 1) {
                                if (!scoreScreen.loadScores("score.txt")) {
                                    std::cerr << "Error for charging the score.\n";
                                }
                                currentScreen = Screen::Scores;
                            }
                        }
                    }
                    else if (currentScreen == Screen::Scores) {
                        if (scoreScreen.handleEvent(*evenement)) {
                            if (scoreScreen.shouldExit()) {
                                currentScreen = Screen::Menu;
                            }
                        }
                    }
                }
            }
            else if (evenement->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = evenement->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                    if (currentScreen == Screen::Map) {
                        gameScene.handleClick(worldPos);
                    }
                }
            }
        }

        window.clear();

        if (currentScreen == Screen::Menu) {
            window.draw(backgroundSprite);
            menu.dessiner(window);
        }
        else if (currentScreen == Screen::Map) {
            window.draw(mapSprite);

            float elapsed = gameClock.getElapsedTime().asSeconds();
            hud.updateTimer(elapsed);

            float deltaTime = deltaClock.restart().asSeconds();

            gameScene.update(deltaTime);
            gameScene.draw(window);
            hud.draw(window);
        }
        else if (currentScreen == Screen::Scores) {
            scoreScreen.draw(window);
        }

        window.display();
    }

    return 0;
}
