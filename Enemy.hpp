//
// Created by nadjl on 13/06/2025.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#pragma once

#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy {
public:
    Enemy(int id, float health, sf::Vector2f pos, float speed, std::shared_ptr<sf::Texture> texture)
        : id(id), health(health), position(pos), speed(speed), texture(texture), sprite(*texture)
    {
        if (!this->texture) {
            std::cerr << "Error : invalid texture\n";
            return;
        }

        // Centrage du sprite
        sprite.setOrigin(sf::Vector2f(texture->getSize()));
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(2.5f, 2.5f));

        {
            maxHealth = 40;
            currentHealth = 40;

            // Initialisation des barres
            healthBarBack.setSize(sf::Vector2f(50.f, 6.f)); // fixed width
            healthBarBack.setFillColor(sf::Color(50, 50, 50)); // grey

            healthBar.setSize(sf::Vector2f(0.7f, 2.f));
            healthBar.setFillColor(sf::Color::Green);
        }

    }

    void update(float deltaTime) {


        position.x -= speed * deltaTime;
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

    bool isDead() const {
        return currentHealth <= 0.f;
    }

    bool hasReachedWall(float wallX) {
        if (!reachedWall && position.x <= wallX) {
            reachedWall = true;
            return true;
        }
        return false;
    }


private:
    int id;
    float health;
    sf::Vector2f position;
    float speed;

    // health bar
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBar;

    float maxHealth;
    float currentHealth;
    bool reachedWall = false;


    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};


#endif //ENEMY_HPP
