#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.hpp"
#include "Tower.hpp"
#include "GameState.hpp"

class GameScene {
public:
    GameScene(sf::RenderWindow& window);
    GameScene(sf::RenderWindow& window, GameState* gameState);

    void loadAssets();
    void update(float deltaTime);
    void handleClick(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void spawnEnemies();

private:
    sf::RenderWindow& window;  // <-- RÉFÉRENCE
    GameState* gameState;
    std::shared_ptr<sf::Texture> enemyTexture;
    std::shared_ptr<sf::Texture> towerTexture;

    std::vector<Enemy> enemies;
    std::vector<Tower> towers;

    int nextTowerId = 1;
    float timeSinceLastWave = 0.f;
};

#endif
