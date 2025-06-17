#include "Tower.hpp"

    Tower::Tower(int id, float range, float fireRate, sf::Vector2f position, std::shared_ptr<sf::Texture> texture)
        : id(id), range(range), fireRate(fireRate), position(position), texture(texture), sprite(*texture), timeSinceLastShot(0.f)
{
    if (!texture) {
        std::cerr << "Texture pointer is null" << std::endl;
        return;
    }

    sprite.setOrigin(sf::Vector2f(texture->getSize()) / 2.f);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(2.5f, 2.5f));
}

void Tower::update(float deltaTime) {
    timeSinceLastShot += deltaTime;
}

void Tower::tryFireAtEnemy(Enemy& enemy) {
    float dx = enemy.getPosition().x - position.x;
    float dy = enemy.getPosition().y - position.y;
    float distSq = dx * dx + dy * dy;

    if (distSq < range * range && timeSinceLastShot >= fireRate) {
        enemy.takeDamage(10.f);
        timeSinceLastShot = 0.f;
    }
}

void Tower::tryFireAtEnemies(std::vector<Enemy>& enemies) {
    for (auto& enemy : enemies) {
        tryFireAtEnemy(enemy);
    }
}

void Tower::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
