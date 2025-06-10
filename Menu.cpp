#include "Menu.h"

Menu::Menu(float largeur, float hauteur, sf::Font &police)
    : indexSelectionne(0),
      elementsMenu{
          sf::Text(police),
          sf::Text(police),
          sf::Text(police)
      }
{
    std::string libelles[MAX_ITEM] = {"Play", "Difficulty", "Quit"};

    float paddingX = 20.f;
    float paddingY = 10.f;

    for (int i = 0; i < MAX_ITEM; i++) {
        elementsMenu[i].setString(sf::String::fromUtf8(libelles[i].begin(), libelles[i].end()));
        elementsMenu[i].setCharacterSize(36);
        elementsMenu[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        elementsMenu[i].setPosition(
            sf::Vector2f(largeur / 2.f - 60.f, hauteur / (MAX_ITEM + 1) * (i + 1))
        );
    }
}

void Menu::dessiner(sf::RenderWindow &fenetre) {
    for (int i = 0; i < MAX_ITEM; i++)
        fenetre.draw(elementsMenu[i]);
}

void Menu::monter() {
    if (indexSelectionne > 0) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        indexSelectionne--;
        elementsMenu[indexSelectionne].setFillColor(sf::Color::Red);
    }
}

void Menu::descendre() {
    if (indexSelectionne < MAX_ITEM - 1) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        indexSelectionne++;
        elementsMenu[indexSelectionne].setFillColor(sf::Color::Red);
    }
}

int Menu::getIndexSelectionne() const {
    return indexSelectionne;
}
