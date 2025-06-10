#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"

Menu::Menu(float largeur, float hauteur, sf::Font &police)
    : indexSelectionne(0),
      elementsMenu{
          sf::Text(police),
          sf::Text(police),
          sf::Text(police)
      }
{
    const std::string labels[] = { "Play", "Difficulty", "Quit" };
    float posX = largeur / 2.f;
    float posY = hauteur / 2.f;

    for (int i = 0; i < 3; ++i)
    {
        elementsMenu[i].setFont(police);
        elementsMenu[i].setString(labels[i]);
        elementsMenu[i].setCharacterSize(40);
        elementsMenu[i].setFillColor(i == 0 ? sf::Color(255, 255, 0) : sf::Color::White); // Jaune si sélectionné

        sf::FloatRect bounds = elementsMenu[i].getLocalBounds();
        float widthText = bounds.size.x;
        float heightText = bounds.size.y;
        float topOffset = bounds.position.y;

        elementsMenu[i].setOrigin(sf::Vector2f(widthText / 2.f, heightText / 2.f + topOffset));
        elementsMenu[i].setPosition(sf::Vector2f(posX, posY + i * 100.f));

        float paddingX = 60.f;
        float paddingY = 40.f;

        fondMenu[i].setSize(sf::Vector2f(widthText + paddingX, heightText + paddingY));
        fondMenu[i].setCornersRadius(20.f);

        // Couleurs rétro pixel art
        if (i == 0)
            fondMenu[i].setFillColor(sf::Color(106, 190, 48, 220)); // Vert doux
        else
            fondMenu[i].setFillColor(sf::Color(34, 32, 52, 180)); // Violet foncé

        fondMenu[i].setOutlineThickness(2.f);
        fondMenu[i].setOutlineColor(sf::Color(255, 255, 255, 120)); // blanc doux

        fondMenu[i].setPosition(sf::Vector2f(
            posX - (widthText + paddingX) / 2.f,
            (posY + i * 100.f) - (heightText + paddingY) / 2.f
        ));
    }
}

void Menu::dessiner(sf::RenderWindow &fenetre) {
    for (int i = 0; i < MAX_ITEM; i++) {
        // Ombre portée
        sf::Text ombre = elementsMenu[i];
        ombre.move(sf::Vector2f(2.f, 2.f));// décalage ombre
        ombre.setFillColor(sf::Color(0, 0, 0, 150)); // noir transparent
        fenetre.draw(fondMenu[i]);
        fenetre.draw(ombre); // dessiner l’ombre d’abord
        fenetre.draw(elementsMenu[i]); // puis le texte
    }
}


void Menu::monter() {
    if (indexSelectionne > 0) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        fondMenu[indexSelectionne].setFillColor(sf::Color(34, 32, 52, 180)); // non-sélectionné

        indexSelectionne--;

        elementsMenu[indexSelectionne].setFillColor(sf::Color(255, 255, 0)); // Jaune
        fondMenu[indexSelectionne].setFillColor(sf::Color(106, 190, 48, 220)); // Vert doux
    }
}

void Menu::descendre() {
    if (indexSelectionne < MAX_ITEM - 1) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        fondMenu[indexSelectionne].setFillColor(sf::Color(34, 32, 52, 180));

        indexSelectionne++;

        elementsMenu[indexSelectionne].setFillColor(sf::Color(255, 255, 0));
        fondMenu[indexSelectionne].setFillColor(sf::Color(106, 190, 48, 220));
    }
}

int Menu::getIndexSelectionne() const {
    return indexSelectionne;
}

