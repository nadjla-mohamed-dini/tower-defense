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
void GameState::defeatEnemy() {
    // Ex: décrémente un compteur interne, à toi de gérer les détails
}

bool GameState::hasEnemyReachedWall() const {
    // retourne une variable membre booléenne (à créer si nécessaire)
    return false; // par défaut
}

int GameState::getEnemiesRemaining() const {
    // retourne une variable membre int (à créer si nécessaire)
    return 0; // par défaut
}

void GameState::resetGame() {
    score = 0;
    lives = 3;
    round = 1;
    gain = 0;
    // Remets à 0 aussi enemiesRemaining, enemyReachedWall etc. si tu les utilises
    notifyObservers();
}

