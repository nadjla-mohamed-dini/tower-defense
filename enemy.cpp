#include <iostream>

struct Vector2f {
    float x;
    float y;

    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
};

class Enemy {
private:
    int health;
    float speed;
    Vector2f position;
    int damage;

public:
    Enemy(int hp, float spd, Vector2f pos, int dmg)
        : health(hp), speed(spd), position(pos), damage(dmg) {}

    int getHealth() const { return health; }
    float getSpeed() const { return speed; }
    Vector2f getPosition() const { return position; }
    int getDamage() const { return damage; }

    void setPosition(const Vector2f& pos) { position = pos; }

    // Infliger des dégâts
    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }
    bool isAlive() const {
        return health > 0;
    }

    // Mise à jour position vitesse/temps
    void update(float deltaTime) {
        position.x += speed * deltaTime;
    }

    void printStatus() const {
        std::cout << "Enemy at (" << position.x << ", " << position.y << "), "
                  << "HP: " << health << ", Speed: " << speed
                  << ", Damage: " << damage << std::endl;
    }
};

int main() {
    Enemy enemy(100, 50.0f, Vector2f(0.0f, 0.0f), 10);

    enemy.printStatus();

    enemy.update();
    enemy.printStatus();

    enemy.takeDamage();
    enemy.printStatus();

    return 0;
}
