#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include<vector>
#include "Observateur .hpp"

class GameState {
private:
    int score = 0;
    int lives = 3;
    int round = 1;
    int gain = 0;

    std::vector<Observer*> observers;
public:
    void registerObserver(Observer* observer);
    void notifyObservers();

    void addScore(int s);
    void loseLives(int life = 1);
    void nextRound();
    void addGain(int g);

};
#endif //GAMESTATE_HPP


