#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <iostream>

class Tower {
public:
    Tower(int id, float range, float fireRate, sf::Vector2f pos, std::shared_ptr<sf::Texture> texture)
        : id(id), range(range), fireRate(fireRate), position(pos), texture(texture), sprite(*texture), timeSinceLastShot(0.f)
    {
        if (!texture || !texture->loadFromFile("images/mage_yellow_stage3_1.png")) {
            std::cerr << "Erreur: texture invalide\n";
            return;
        }

        sprite.setOrigin(sf::Vector2f(texture->getSize()) / 2.f);
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(2.5f, 2.5f));
    }

    void update(float deltaTime) {
        timeSinceLastShot += deltaTime;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void tryFireAtEnemy(Enemy& enemy) {
        float dx = enemy.getPosition().x - position.x;
        float dy = enemy.getPosition().y - position.y;
        float distSq = dx * dx + dy * dy;

        if (distSq < range * range && timeSinceLastShot >= fireRate) {
            std::cout << "Tower " << id << " is firing at enemy!" << std::endl;
            enemy.takeDamage(10.f);
            timeSinceLastShot = 0.f;
        }
    }

private:
    int id;
    float range;
    float fireRate;
    float timeSinceLastShot;

    sf::Vector2f position;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};
