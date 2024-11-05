#include <SFML/Graphics.hpp>
#include "Pathfinder.hpp"

void    fixWindowPos(sf::RenderWindow &window)
{
     // Get monitor size
    sf::Vector2i monitorSize;
    monitorSize.x = sf::VideoMode::getDesktopMode().width;
    monitorSize.y = sf::VideoMode::getDesktopMode().height;

    // Center monitor
    sf::Vector2i windowPos;
    windowPos.x = monitorSize.x / 2 - window.getSize().x / 2;
    windowPos.y = monitorSize.y / 2 - window.getSize().y / 2;
    window.setPosition(windowPos);

}

int main()
{
    // Constant variables
    const int   windowTileWidth = 20; // in tiles
    const int   windowTileHeight = 17; // in tiles
    const int   tileSize = 80;

    auto window = sf::RenderWindow({tileSize * windowTileWidth, tileSize * windowTileHeight}, "A* Pathfinder");
    window.setFramerateLimit(144);

    fixWindowPos(window);

    Pathfinder  finder(windowTileWidth, windowTileHeight, tileSize);
	finder.getInfoBox().initInfoBox(window, tileSize);

    // Rendering loop
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed \
            || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

			if (event.type == sf::Event::KeyPressed && finder.getState() == CLICKED)
				finder.checkClickedInput(event);

            if (event.type == sf::Event::MouseButtonPressed \
            && event.mouseButton.button == sf::Mouse::Button::Left)
                finder.checkMousePress(window);
        }

        window.clear();

        finder.drawGrid(window);

		finder.getInfoBox().draw(window, finder.getState());

        window.display();
    }
}
