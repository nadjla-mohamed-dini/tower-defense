#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>

const int CELL_SIZE = 64;

sf::Color getColorForType(const std::string& type) {
    if (type == "vide") return sf::Color::White;
    if (type == "chemin") return sf::Color(150, 75, 0); // marron
    if (type == "tour") return sf::Color::Blue;
    return sf::Color::Black;
}
class Case {
    std::string type = "vide";
public:
    const std::string& getType() const { return type; }
    void setType(const std::string& t) { type = t; }
};

// Classe Map
class Map {
    int rows, cols;
    std::vector<std::vector<Case>> grid;
public:
    Map(int r, int c) : rows(r), cols(c), grid(r, std::vector<Case>(c)) {}

    Case& getCase(int x, int y) {
        if (x < 0 || x >= cols || y < 0 || y >= rows)
            throw std::out_of_range("Coordonnées hors grille");
        return grid[y][x];
    }
};

int main() {
    int rows = 5;
    int cols = 5;

    Map map(rows, cols);
    for (int x = 0; x < cols; ++x)
        map.getCase(x, 2).setType("chemin");

    // SFML 3 : sf::VideoMode prend un Vector2u
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(cols * CELL_SIZE),
                                           static_cast<unsigned>(rows * CELL_SIZE)}),
                            "Tower Defense");

    while (window.isOpen()) {
        while (auto eventOpt = window.pollEvent()) {
            auto& event = *eventOpt;

            if (event.is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    int x = mousePressed->position.x / CELL_SIZE;
                    int y = mousePressed->position.y / CELL_SIZE;

                    try {
                        Case& cell = map.getCase(x, y);
                        if (cell.getType() == "vide") {
                            cell.setType("tour");
                        }
                    } catch (const std::out_of_range&) {
                        // Ignore clicks outside grid
                    }
                }
            }
        }

        window.clear();

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                rect.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                rect.setFillColor(getColorForType(map.getCase(x, y).getType()));
                window.draw(rect);
            }
        }

        window.display();
    }

    return 0;
}
