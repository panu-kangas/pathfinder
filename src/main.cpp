#include <SFML/Graphics.hpp>
#include "Pathfinder.hpp"

#include "FinderAlgo.hpp"

void    fixWindowPos(sf::RenderWindow &window)
{
     // Get monitor size
    sf::Vector2i monitorSize;
    monitorSize.x = sf::VideoMode::getDesktopMode().width;
    monitorSize.y = sf::VideoMode::getDesktopMode().height;

// Use this only after you've fixed all of the window.getSize() functions out

//	float	height = monitorSize.y * 0.8;

//	if (height > window.getSize().y)
//	{
//		sf::Vector2u	newSize;
//		newSize.x = height;
//		newSize.y = height;
//		window.setSize(newSize);
//	}


    // Center monitor
    sf::Vector2i windowPos;
    windowPos.x = monitorSize.x / 2 - window.getSize().x / 2;
    windowPos.y = monitorSize.y / 2 - window.getSize().y / 2;
    window.setPosition(windowPos);

}

int main()
{
    // Constant variables
    const int   windowTileWidth = 17; // in tiles
    const int   windowTileHeight = 17; // in tiles
    const int   tileSize = 40;

	// IDEA! Create a const variable "gameWindowSize", that is passed on & stored around
	// That way I don't need to use the window.getSize() function anywhere, and the scale will
	// remain untouched

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

	// FIX THIS! It works, but you need to make it static somehow...
	// It is NOT supposed to happen on every frame!
/*
		if (finder.getStartPos().x != -1 && finder.getFinishPos().x != -1)
		{
			FinderAlgo algo(finder.getStartPos(), finder.getFinishPos());
			algo.countDistances(finder.getGridVec());
			algo.draw(window, finder.getGridVec());
		}
*/

        window.display();
    }
}
