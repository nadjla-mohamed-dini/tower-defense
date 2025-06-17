#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"
#include <iostream>


Menu::Menu(float width, float height, sf::Font &police)
    : indexSelectionne(0),
      elementsMenu{
          sf::Text(police),
          sf::Text(police),
          sf::Text(police)
      }

{


    const std::string labels[] = { "Play", "Score", "Quit" };
    float posX = width / 2.f;
    float posY = height / 2.f;

    for (int i = 0; i < 3; ++i)
    {
        elementsMenu[i].setFont(police);
        elementsMenu[i].setString(labels[i]);
        elementsMenu[i].setCharacterSize(40);
        elementsMenu[i].setFillColor(i == 0 ? sf::Color(255, 255, 0) : sf::Color::White);

        sf::FloatRect bounds = elementsMenu[i].getLocalBounds();
        float widthText = bounds.size.x;
        float heightText = bounds.size.y;
        float topOffset = bounds.position.y;

        elementsMenu[i].setOrigin(sf::Vector2f(widthText / 2.f, heightText / 2.f + topOffset));
        elementsMenu[i].setPosition(sf::Vector2f(posX, posY + i * 100.f));

        float paddingX = 60.f;
        float paddingY = 40.f;

        backgroundMenu[i].setSize(sf::Vector2f(widthText + paddingX, heightText + paddingY));
        backgroundMenu[i].setCornersRadius(20.f);


        if (i == 0)
            backgroundMenu[i].setFillColor(sf::Color(106, 190, 48, 220)); // soft green
        else
            backgroundMenu[i].setFillColor(sf::Color(34, 32, 52, 180)); // dartk purple

        backgroundMenu[i].setOutlineThickness(2.f);
        backgroundMenu[i].setOutlineColor(sf::Color(255, 255, 255, 120)); // soft white

        backgroundMenu[i].setPosition(sf::Vector2f(
            posX - (widthText + paddingX) / 2.f,
            (posY + i * 100.f) - (heightText + paddingY) / 2.f
        ));
    }
}

void Menu::dessiner(sf::RenderWindow &window) {
    for (int i = 0; i < MAX_ITEM; i++) {
        // Ombre portée
        sf::Text shadow = elementsMenu[i];
        shadow.move(sf::Vector2f(2.f, 2.f));
        shadow.setFillColor(sf::Color(0, 0, 0, 150)); // transparent black
        window.draw(backgroundMenu[i]);
        window.draw(shadow);
        window.draw(elementsMenu[i]);
    }
}


void Menu::monter() {
    if (indexSelectionne > 0) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        backgroundMenu[indexSelectionne].setFillColor(sf::Color(34, 32, 52, 180)); // non-sélectionné

        indexSelectionne--;

        elementsMenu[indexSelectionne].setFillColor(sf::Color(255, 255, 0)); // Jaune
        backgroundMenu[indexSelectionne].setFillColor(sf::Color(106, 190, 48, 220)); // Vert doux
    }
}

void Menu::descendre() {
    if (indexSelectionne < MAX_ITEM - 1) {
        elementsMenu[indexSelectionne].setFillColor(sf::Color::White);
        backgroundMenu[indexSelectionne].setFillColor(sf::Color(34, 32, 52, 180));

        indexSelectionne++;

        elementsMenu[indexSelectionne].setFillColor(sf::Color(255, 255, 0));
        backgroundMenu[indexSelectionne].setFillColor(sf::Color(106, 190, 48, 220));
    }
}

int Menu::getIndexSelectionne() const {
    return indexSelectionne;
}


