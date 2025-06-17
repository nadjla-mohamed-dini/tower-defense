#include "HUD.hpp"
#include <sstream>
#include <iomanip>


HUD::HUD(sf::Font &font)
: text(font, "", 20)  // police, chaîne vide, taille
{
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(20.f, 10.f)); // En haut à gauche
}



void HUD::update(int score, int lives, int round, int gain) {
    currentScore = score;
    currentLives = lives;
    currentRound = round;
    currentGain = gain;
    updateDisplayString();
}

void HUD::updateGain(int gain) {
    currentGain = gain;
    updateDisplayString();
}

void HUD::updateTimer(float elapsedTime) {
    timer = elapsedTime;
    updateDisplayString();
}

void HUD::updateDisplayString() {
    std::stringstream ss;
    int minutes = static_cast<int>(timer) / 60;
    int seconds = static_cast<int>(timer) % 60;

    ss << "Score: " << currentScore
       << "   Lives: " << currentLives
       << "   Round: " << currentRound
       << "   Gain: " << currentGain
       << "   Time: " << std::setw(2) << std::setfill('0') << minutes
       << ":" << std::setw(2) << std::setfill('0') << seconds;

    text.setString(ss.str());
}

void HUD::draw(sf::RenderWindow &window) {
    window.draw(text);
}
