//
// Created by nadjl on 16/06/2025.
//

#ifndef SCORESCREEN_HPP
#define SCORESCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ScoreScreen {
public:
    ScoreScreen(sf::Font& font);

    // Charged the scores from a file
    bool loadScores(const std::string& filename);


    void draw(sf::RenderWindow& window);

    // Comeback to the menu with a touch
    bool handleEvent(const sf::Event& event);


    bool shouldExit() const;

private:
    sf::Font& font;
    std::vector<int> scores;
    bool exitScreen = false;
};

#endif
