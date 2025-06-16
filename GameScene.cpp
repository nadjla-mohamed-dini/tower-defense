#include "GameScene.hpp"
#include <algorithm>
#include "Enemy.hpp"
#include <iostream>



GameScene::GameScene(sf::RenderWindow& window)
    : window(window), gameState(nullptr) {
}

GameScene::GameScene(sf::RenderWindow& window, GameState* gameState)
    : window(window), gameState(gameState) {
}


void GameScene::loadAssets() {
    towerTexture = std::make_shared<sf::Texture>();
    enemyTexture = std::make_shared<sf::Texture>();

    if (!towerTexture->loadFromFile("asset/mage_yellow_stage3_1.png")) {
        std::cerr << "Error: impossible to charged mage_yellow_stage3_1.png\n";
        // gestion d'erreur ici, par ex. return ou throw
        exit(EXIT_FAILURE);
    }
    if (!enemyTexture->loadFromFile("asset/slime_yellow_stage1.png")) {
        std::cerr << "Error: impossible to charged slime.png\n";
        exit(EXIT_FAILURE);
    }
}

void GameScene::spawnEnemies() {
    assert(gameState != nullptr && "gameState don't have to be nullptr");
    int numEnemies = 1 + gameState->getRound() * 2;

    for (int i = 0; i < numEnemies; ++i) {
        int id = i;
        float health = 50.f;
        sf::Vector2f position(900.f + i * 100.f, 400.f);
        enemies.emplace_back(Enemy(i, 50.f, position, 30.f, enemyTexture));
        float speed = 30.f;

        Enemy enemy(id, health, position, speed, enemyTexture);
        enemies.push_back(enemy);
    }

}

void GameScene::update(float deltaTime) {
    timeSinceLastWave += deltaTime;

    // MAJ the tower
    for (auto& tower : towers) {
        tower.update(deltaTime);
        tower.tryFireAtEnemies(enemies);
    }

    for (auto& enemy : enemies) {
        enemy.update(deltaTime);
    }

    // Handle the death + coins
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy& e) {
        if (e.isDead()) {
            gameState->addScore(10);
            gameState->addGain(2);
            return true;
        }
        return false;
    }), enemies.end());

    // next round if everybody died
    if (enemies.empty() && timeSinceLastWave >= 5.0f) {
        gameState->nextRound();  // // Increment the round here, before the new wave
        spawnEnemies();
        timeSinceLastWave = 0.f;
    }
}

void GameScene::draw(sf::RenderWindow& window) {
    for (auto& tower : towers)
        tower.draw(window);
    for (auto& enemy : enemies)
        enemy.draw(window);
}

void GameScene::handleClick(const sf::Vector2f& position) {
    Tower tower(nextTowerId++, 150.f, 1.0f, position, towerTexture);
    towers.push_back(tower);
}