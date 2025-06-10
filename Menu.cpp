#include "Menu.h"
#include <SFML/Graphics.hpp>

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
        elementsMenu[i].setFillColor(sf::Color::White);

        // SFML 3 : Nouvelle syntaxe pour sf::FloatRect
        sf::FloatRect bounds = elementsMenu[i].getLocalBounds();
        float widthText = bounds.size.x;      // Largeur (anciennement width())
        float heightText = bounds.size.y;     // Hauteur (anciennement height())
        float topOffset = bounds.position.y;  // Position Y (anciennement top())

        elementsMenu[i].setOrigin(sf::Vector2f(widthText / 2.f, heightText / 2.f + topOffset));
        elementsMenu[i].setPosition(sf::Vector2f(posX, posY + i * 100.f));

        float paddingX = 40.f;
        float paddingY = 30.f;

        // SFML 3 : setCornerRadius() (au singulier) au lieu de setCornersRadius()
        fondMenu[i].setSize(sf::Vector2f(widthText + paddingX, heightText + paddingY));
        fondMenu[i].setCornersRadius(15.f);
        fondMenu[i].setFillColor(i == 0 ? sf::Color(200, 0, 0) : sf::Color(150, 150, 150));
        fondMenu[i].setOutlineThickness(2.f);
        fondMenu[i].setOutlineColor(sf::Color::Black);

        fondMenu[i].setPosition(sf::Vector2f(
            posX - (widthText + paddingX) / 2.f,
            (posY + i * 100.f) - (heightText + paddingY) / 2.f
        ));
    }
}


void Menu::dessiner(sf::RenderWindow &fenetre) {
    for (int i = 0; i < MAX_ITEM; i++) {
        fenetre.draw(fondMenu[i]);
        fenetre.draw(elementsMenu[i]);
    }
}

void Menu::monter() {
    if (indexSelectionne > 0) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        fondMenu[indexSelectionne].setFillColor(sf::Color(100, 100, 100));
        indexSelectionne--;
        elementsMenu[indexSelectionne].setFillColor(sf::Color::Red);
        fondMenu[indexSelectionne].setFillColor(sf::Color(200, 0, 0));
    }
}

void Menu::descendre() {
    if (indexSelectionne < MAX_ITEM - 1) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        fondMenu[indexSelectionne].setFillColor(sf::Color(100, 100, 100));
        indexSelectionne++;
        elementsMenu[indexSelectionne].setFillColor(sf::Color::Red);
        fondMenu[indexSelectionne].setFillColor(sf::Color(200, 0, 0));
    }
}

int Menu::getIndexSelectionne() const {
    return indexSelectionne;
}
