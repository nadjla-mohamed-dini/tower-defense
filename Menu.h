#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"

#define MAX_ITEM 3

class Menu {
public:
    Menu(float largeur, float hauteur, sf::Font &police);

    void dessiner(sf::RenderWindow &fenetre);
    void monter();
    void descendre();
    int getIndexSelectionne() const;
    void startAnimation();



private:
    int indexSelectionne;
    sf::Text elementsMenu[MAX_ITEM];
    RoundedRectangleShape fondMenu[MAX_ITEM];

    //Variable d'animation
    bool isAnimating = true;
    float Animatedtimer = 0.f;
    sf::Vector2f startPositions [MAX_ITEM];



};

#endif // MENU_H
