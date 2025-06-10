#include <SFML/Graphics.hpp>
#include <optional>
#include "Menu.h"
#include <iostream>

int main() {
    sf::RenderWindow fenetre(sf::VideoMode({800, 600}), "Menu du jeu");

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

    while (fenetre.isOpen()) {
        while (auto evenement = fenetre.pollEvent()) {
            if (evenement->is<sf::Event::Closed>()) {
                fenetre.close();
            }
            else if (evenement->is<sf::Event::KeyPressed>()) {
                auto touche = evenement->getIf<sf::Event::KeyPressed>();
                if (touche) {
                    if (touche->code == sf::Keyboard::Key::Up) {
                        menu.monter();
                    }
                    else if (touche->code == sf::Keyboard::Key::Down) {
                        menu.descendre();
                    }
                    else if (touche->code == sf::Keyboard::Key::Enter) {
                        int choix = menu.getIndexSelectionne();
                        // Gestion du choix du menu
                    }
                }
            }
        }

        fenetre.clear();
        fenetre.draw(backgroundSprite); // Fond
        menu.dessiner(fenetre);         // Menu par-dessus
        fenetre.display();
    }

    return 0;
}
