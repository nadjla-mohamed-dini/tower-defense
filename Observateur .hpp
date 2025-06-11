#ifndef OBSERVATEUR_HPP
#define OBSERVATEUR_HPP

class Observer {
public:
    virtual void update(int score, int lives, int round) = 0;
    virtual ~Observer() {}
};

#endif //OBSERVATEUR_HPP


