#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.hpp"
#include "Tower.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Enemy Tower");
    sf::Clock clock;

    auto sharedEnemyTexture = std::make_shared<sf::Texture>();
    if (!sharedEnemyTexture->loadFromFile("images/slime_yellow_stage1.png")) {
        std::cerr << "Erreur: impossible de charger l'image slime_yellow_stage1.png\n";
        return -1;
    }

    auto sharedTowerTexture = std::make_shared<sf::Texture>();
    if (!sharedTowerTexture->loadFromFile("images/mage_yellow_stage3_1.png")) {
        std::cerr << "Erreur: impossible de charger l'image mage_yellow_stage3_1.png\n";
        return -1;
    }

    std::vector<Enemy> ennemies;
    ennemies.emplace_back(1, 100.f, sf::Vector2f{200.f, 200.f}, 0.3f, sharedEnemyTexture);
    ennemies.emplace_back(2, 100.f, sf::Vector2f{250.f, 250.f}, 0.2f, sharedEnemyTexture);
    ennemies.emplace_back(3, 100.f, sf::Vector2f{300.f, 300.f}, 0.4f, sharedEnemyTexture);

    std::vector<Tower> towers;

    // Optionnel : une tour au début
    towers.emplace_back(1, 150.f, 1.0f, sf::Vector2f{400.f, 300.f}, sharedTowerTexture);

    int nextTowerId = 2;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (auto optEvent = window.pollEvent()) {
            if (optEvent->is<sf::Event::Closed>()) {
                window.close();
            }

            if (optEvent->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = optEvent->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent->button == sf::Mouse::Button::Left){
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    towers.emplace_back(nextTowerId++, 150.f, 1.0f, worldPos, sharedTowerTexture);
                }
            }
        }

        window.clear();

        for (auto& enemy : ennemies)
            enemy.update();

        for (auto& tower : towers) {
            tower.update(deltaTime);
            for (auto& enemy : ennemies) {
                tower.tryFireAtEnemy(enemy);
            }
            tower.draw(window);
        }

        for (auto& enemy : ennemies)
            enemy.draw(window);

        window.display();
    }

    return 0;
}
