// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"

#define MAX_ITEM 3

class Menu {
public:
    Menu(float width, float height, sf::Font &police);

    void dessiner(sf::RenderWindow &window);
    void monter();
    void descendre();
    int getIndexSelectionne() const;



private:
    int indexSelectionne;
    sf::Text elementsMenu[MAX_ITEM];
    RoundedRectangleShape backgroundMenu[MAX_ITEM];

};

#endif // MENU_H
