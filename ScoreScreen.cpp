//
// Created by nadjl on 16/06/2025.
//

#include "ScoreScreen.hpp"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
ScoreScreen::ScoreScreen(sf::Font& f) : font(f) {}

bool ScoreScreen::loadScores(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error : unable to open the file " << filename << std::endl;


        return false;
    }
    scores.clear();
    int score;
    while (file >> score) {
        scores.push_back(score);
    }
    if (file.bad()) {
        std::cerr << "Error while reading file." << std::endl;
        return false;
    }
    return true;
}

void ScoreScreen::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    sf::Text text(font);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    for (size_t i = 0; i < scores.size(); ++i) {
        text.setString("Score " + std::to_string(i + 1) + ": " + std::to_string(scores[i]));
        text.setPosition(sf::Vector2f(50.f, 50.f + static_cast<float>(i) * 30.f));
        window.draw(text);
    }

}
bool ScoreScreen::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto& keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Escape) {
            exitScreen = true;
            return true;
        }
    }
    return false;
}


bool ScoreScreen::shouldExit() const {
    return exitScreen;
}
