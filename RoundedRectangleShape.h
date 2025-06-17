//
// Created by nadjl on 10/06/2025.
//

#ifndef ROUNDEDRECTANGLESHAPE_H
#define ROUNDEDRECTANGLESHAPE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangleShape : public sf::Shape {
public:
    explicit RoundedRectangleShape(sf::Vector2f size = {0,0}, float radius = 0, std::size_t cornerPointCount = 20)
        : m_size(size), m_radius(radius), m_cornerPointCount(cornerPointCount) {
        update();
    }

    void setSize(sf::Vector2f size) {
        m_size = size;
        update();
    }

    sf::Vector2f getSize() const {
        return m_size;
    }

    void setCornersRadius(float radius) {
        m_radius = radius;
        update();
    }

    float getCornersRadius() const {
        return m_radius;
    }

    void setCornerPointCount(std::size_t count) {
        m_cornerPointCount = count;
        update();
    }

    std::size_t getPointCount() const override {
        return m_cornerPointCount * 4;
    }

    sf::Vector2f getPoint(std::size_t index) const override {
        std::size_t corner = index / m_cornerPointCount;
        float angle = (index % m_cornerPointCount) * 90.f / (m_cornerPointCount - 1);
        float rad = angle * 3.141592654f / 180.f;

        sf::Vector2f center;
        switch (corner) {
            case 0: center = {m_size.x - m_radius, m_radius}; break;
            case 1: center = {m_radius, m_radius}; break;
            case 2: center = {m_radius, m_size.y - m_radius}; break;
            case 3: center = {m_size.x - m_radius, m_size.y - m_radius}; break;
        }

        return {center.x + m_radius * std::cos(rad), center.y - m_radius * std::sin(rad)};
    }

private:
    sf::Vector2f m_size;
    float m_radius;
    std::size_t m_cornerPointCount;
};

#endif //ROUNDEDRECTANGLESHAPE_H
