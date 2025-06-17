#ifndef OBSERVATEUR_HPP
#define OBSERVATEUR_HPP

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(int score, int lives, int round, int gain) = 0;

};

#endif //OBSERVATEUR_HPP


