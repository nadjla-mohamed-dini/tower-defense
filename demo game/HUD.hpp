//
// Created by nadjl on 11/06/2025.
//

#ifndef HUD_HPP
#define HUD_HPP
#include <SFML/Graphics.hpp>

#include "Observateur .hpp"


class HUD: public Observer{
public:
    HUD(sf::Font& font);

    void update(int score, int lives, int round,int gain) override;
    void updateGain(int gain);
    void updateTimer(float elapsedTime);

    void draw(sf::RenderWindow& window);

private:
    sf::Text text;
    int currentScore = 0;
    int currentLives = 3;
    int currentRound = 0;
    int currentGain = 0;
    float timer = 0.f;

    void updateDisplayString();

};

#endif //HUD_HPP
