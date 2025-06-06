#include <SFML/Graphics.hpp>

int main()
{
    // Création de la fenêtre
    sf::RenderWindow window({800, 600}, "Tower Defence");

    // Chargement de la texture de fond
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/terrain.png")) {
        return -1;
    }

    // Création d'un sprite pour afficher l'image
    sf::Sprite backgroundSprite(backgroundTexture);

    // Boucle principale
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }

    return 0;
}
