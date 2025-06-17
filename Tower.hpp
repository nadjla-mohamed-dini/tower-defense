#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <memory>
#include <vector>

class Tower {
public:
    Tower(int id, float range, float fireRate, sf::Vector2f position, std::shared_ptr<sf::Texture> texture);

    void update(float deltaTime);

    void tryFireAtEnemy(Enemy& enemy);

    void tryFireAtEnemies(std::vector<Enemy>& enemies);

    void draw(sf::RenderWindow& window);

private:
    int id;
    float range;
    float fireRate;
    float timeSinceLastShot;

    sf::Vector2f position;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};

#endif // TOWER_HPP
