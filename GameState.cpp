//
// Created by nadjl on 11/06/2025.
//
#include "GameState.hpp"

void GameState::registerObserver(Observer *observer) {
    observers.push_back(observer);
}

void GameState::notifyObservers() {
    for (Observer* observer: observers) {
        observer ->update(score, lives, round, gain);

    }
}

void GameState::loseLives(int life) {
    if (lives > 0) {
        lives -= life;
        if (lives < 0) lives = 0;
    }
    notifyObservers();
}

void GameState::addScore( const int s) {
    score += s;
    notifyObservers();
}

void GameState::nextRound() {
    round++;
    notifyObservers();
}

void GameState::addGain(int g) {
    gain += g;
    notifyObservers();
}
int GameState::getRound() const {
    return round;
}


//New
void GameState::setEnemiesRemaining(int count) {
    enemiesRemaining = count;
}

void GameState::defeatEnemy() {
    if (enemiesRemaining > 0) {
        enemiesRemaining--;
    }
}

int GameState::getEnemiesRemaining() const {
    return enemiesRemaining;
}

void GameState::setEnemyReachedWall(bool reached) {
    enemyReachedWall = reached;
}

bool GameState::hasEnemyReachedWall() const {
    return enemyReachedWall;
}

void GameState::resetGame() {
    score = 0;
    lives = 3;
    round = 1;
    gain = 0;
    enemiesRemaining = 0;
    enemyReachedWall = false;
    notifyObservers();
}