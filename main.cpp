#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <optional>
#include "Menu.h"
#include "GameState.hpp"
#include "HUD.hpp"
#include <iostream>

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

    GameState gameState;
    HUD hud(police);
    gameState.registerObserver(&hud);
    sf::Clock gameClock;

    enum class Screen { Menu, Map };
    Screen currentScreen = Screen::Menu;

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
                                // Jouer -> passer à l'écran Map
                                currentScreen = Screen::Map;
                                gameClock.restart();  // Reset timer au début du jeu
                            } else if (choix == 1) {
                                fenetre.close();
                            }
                        }
                    }
                    else if (currentScreen == Screen::Map) {
                        if (touche->code == sf::Keyboard::Key::Escape) {
                            currentScreen = Screen::Menu;
                        }
                        //TEST POUR SAVOIR SI SA MARCHE
                        if (touche->code == sf::Keyboard::Key::S) {
                            gameState.addScore(10);
                        }
                        if (touche->code == sf::Keyboard::Key::G) {
                            gameState.addGain(5);
                            hud.updateGain(5);
                        }
                        if (touche->code == sf::Keyboard::Key::R) {
                            gameState.nextRound();
                        }
                        if (touche->code == sf::Keyboard::Key::L) {
                            gameState.loseLives();
                        }
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
            hud.draw(fenetre);
        }

        fenetre.display();
    }

    return 0;
}
