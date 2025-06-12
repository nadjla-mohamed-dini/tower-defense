#include <SFML/Graphics.hpp>

int main()
{
    // Create window
    sf::RenderWindow window({640, 360}, "Tower Defence");

    // Change the background default with the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/field.png")) {
        return -1;
    }

    // Define background sprite
    sf::Sprite backgroundSprite(backgroundTexture);

    // Background image size
    float scaleX = 1.55f; // x
    float scaleY = 1.5f; // y

    backgroundSprite.setScale(scaleX, scaleY);

    // Main loop
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
