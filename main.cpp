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
     sf::RenderWindow fenetre(sf::VideoMode({1200, 600}), "Menu du jeu");

    sf::Font police;
    if (!police.openFromFile("asset/font.ttf")) {
        std::cerr << "Erreur chargement police\n";
        return EXIT_FAILURE;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("asset/background_menu.jpg")) {
        std::cerr << "Erreur chargement background\n";
        return EXIT_FAILURE;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = fenetre.getSize();

    sf::Vector2f scale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    backgroundSprite.setScale(scale);

    Menu menu(fenetre.getSize().x, fenetre.getSize().y, police);
    ScoreScreen scoreScreen(police);
    bool scoreLoaded = scoreScreen.loadScores("asset/score.txt");
    if (!scoreLoaded) {
        std::cerr << "Erreur chargement score."<<std::endl;
    }

    HUD hud(police);
    sf::Clock gameClock;
    sf::Clock deltaClock;

    enum class Screen { Menu, Map, Scores };
    Screen currentScreen = Screen::Menu;

    GameState gameState;
    GameScene gameScene(fenetre, &gameState);
    gameState.registerObserver(&hud);
    gameScene.loadAssets();
    gameScene.spawnEnemies();

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("asset/field1.png")) {
        std::cerr << "Erreur chargement de la map\n";
        return EXIT_FAILURE;
    }
    sf::Sprite mapSprite(mapTexture);

    // Ajuster l’échelle de la map pour la fenêtre
    sf::Vector2u mapSize = mapTexture.getSize();
    sf::Vector2f mapScale(
        static_cast<float>(windowSize.x) / mapSize.x,
        static_cast<float>(windowSize.y) / mapSize.y
    );
    mapSprite.setScale(mapScale);

    while (fenetre.isOpen()) {
    while (auto evenement = fenetre.pollEvent()) {
        if (evenement->is<sf::Event::Closed>()) {
            fenetre.close();
        }
        else if (evenement->is<sf::Event::KeyPressed>()) {
            auto touche = evenement->getIf<sf::Event::KeyPressed>();
            if (touche) {
                if (currentScreen == Screen::Menu) {
                    if (touche->code == sf::Keyboard::Key::Up) {
                        menu.monter();
                    }
                    else if (touche->code == sf::Keyboard::Key::Down) {
                        menu.descendre();
                    }
                    else if (touche->code == sf::Keyboard::Key::Enter) {
                        int choix = menu.getIndexSelectionne();
                        if (choix == 0) {
                            currentScreen = Screen::Map;
                            gameClock.restart();
                            deltaClock.restart();
                        }
                        else if (choix == 2) {
                            fenetre.close();
                        }
                        else if (choix == 1) {
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
            if (currentScreen == Screen::Map) {
                auto mouseEvent = evenement->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(fenetre);
                    sf::Vector2f worldPos = fenetre.mapPixelToCoords(pixelPos);
                    gameScene.handleClick(worldPos);
                }
            }
        }
    }

    fenetre.clear();

    if (currentScreen == Screen::Menu) {
        fenetre.draw(backgroundSprite);
        menu.dessiner(fenetre);
    }
    else if (currentScreen == Screen::Map) {
        fenetre.draw(mapSprite);

        float elapsed = gameClock.getElapsedTime().asSeconds();
        hud.updateTimer(elapsed);

        float deltaTime = deltaClock.restart().asSeconds();

        gameScene.update(deltaTime);
        gameScene.draw(fenetre);
        hud.draw(fenetre);
    }
    else if (currentScreen == Screen::Scores) {
        scoreScreen.draw(fenetre);
    }

    fenetre.display();
   }
    return 0;
}


