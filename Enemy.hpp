#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(int id, float health, sf::Vector2f pos, float speed, std::shared_ptr<sf::Texture> texture)
        : id(id), health(health), position(pos), speed(speed), texture(texture), sprite(*texture)
    {
        if (!this->texture) {
            std::cerr << "Erreur : texture invalide\n";
            return;
        }

        // Centrage du sprite
        sprite.setOrigin(sf::Vector2f(texture->getSize()));
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(2.5f, 2.5f));

        {
            maxHealth = 20;
            currentHealth = 20;

            // Initialisation des barres
            healthBarBack.setSize(sf::Vector2f(50.f, 6.f)); // largeur fixe
            healthBarBack.setFillColor(sf::Color(50, 50, 50)); // gris foncé

            healthBar.setSize(sf::Vector2f(0.7f, 2.f));
            healthBar.setFillColor(sf::Color::Green);
        }

    }

    void update() {
        //Positioner la barre de vie au dessus des ennemy

        position.x += speed * 0.1f;
        sprite.setPosition(position);

        sf::Vector2f pos = sprite.getPosition();
        healthBarBack.setPosition(sf::Vector2f(pos.x, pos.y));
        healthBar.setPosition(sf::Vector2f(pos.x, pos.y));

        float ratio = currentHealth / maxHealth;
        healthBar.setScale(sf::Vector2f(50.f * ratio, 6.f));

        if (ratio > 0.6f)
            healthBar.setFillColor(sf::Color::Green);
        else if (ratio > 0.3f)
            healthBar.setFillColor(sf::Color::Yellow);
        else
            healthBar.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        window.draw(healthBar);
        window.draw(healthBarBack);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void takeDamage(float damage) {
        currentHealth -= damage;
        if (currentHealth <= 0)  currentHealth = 0;
    }



private:
    int id;
    float health;
    sf::Vector2f position;
    float speed;

    // Barre de vie
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBar;

    float maxHealth;
    float currentHealth;


    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};
