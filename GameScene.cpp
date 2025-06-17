#include "GameScene.hpp"
#include <algorithm>
#include "Enemy.hpp"
#include <iostream>


#include "GameScene.hpp"

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
        std::cerr << "Erreur: impossible de charger mage_yellow_stage3_1.png\n";
        // gestion d'erreur ici, par ex. return ou throw
        exit(EXIT_FAILURE);
    }
    if (!enemyTexture->loadFromFile("asset/slime_yellow_stage1.png")) {
        std::cerr << "Erreur: impossible de charger slime.png\n";
        exit(EXIT_FAILURE);
    }
}

void GameScene::spawnEnemies() {
    assert(gameState != nullptr && "gameState ne doit pas être nullptr");
    int numEnemies = 1 + gameState->getRound() * 2;

    for (int i = 0; i < numEnemies; ++i) {
        int id = i;
        float health = 50.f;
        sf::Vector2f position(900.f + i * 100.f, 400.f);
        float speed = 30.f;

        enemies.emplace_back(id, health, position, speed, enemyTexture);

    }

}

void GameScene::update(float deltaTime) {
    timeSinceLastWave += deltaTime;

    // Met à jour les tours
    for (auto& tower : towers) {
        tower.update(deltaTime);
        tower.tryFireAtEnemies(enemies);
    }
    const float WALL_X = 0.f; //new


    for (auto& enemy : enemies) {
        enemy.update(deltaTime);

    // New Vérifie si un ennemi a atteint le mur
        if (enemy.hasReachedWall(WALL_X)) {
            gameState->loseLives(1);
            gameState->hasEnemyReachedWall();
        }
    }
    // Gestion des morts + gains
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy& e) {
        if (e.isDead()) {
            gameState->addScore(10);
            gameState->addGain(5);
            gameState->defeatEnemy();
            return true;
        }
        return false;
    }), enemies.end());

    // Vague suivante si tous morts et assez de temps passé
    if (enemies.empty() && timeSinceLastWave >= 5.0f) {
        gameState->nextRound();  // On incrémente le round ici, avant la nouvelle vague
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
void GameScene::reset() {
    enemies.clear();
    towers.clear();
    timeSinceLastWave = 0.f;
    spawnEnemies();  // relance les ennemis pour le nouveau round
}