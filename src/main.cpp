#include <SFML/Graphics.hpp>
#include "Pathfinder.hpp"
#include "FinderAlgo.hpp"


void    fixWindowPos(sf::RenderWindow &window, sf::Vector2u windowPxSize);


int main()
{
    // Constant variables --> Should these be counted base on the monitor size...?
    const int   TileCountHoriz = 17;
    const int   TileCountVert = 17;
    const int   tileSize = 80; // 40 at home, 80 at school

	// Count window size
	sf::Vector2u	windowPxSize;
	windowPxSize.x = tileSize * TileCountHoriz;
	windowPxSize.y = tileSize * TileCountVert;

    auto window = sf::RenderWindow({windowPxSize.x, windowPxSize.y}, "A* Pathfinder");
    window.setFramerateLimit(144);
    fixWindowPos(window, windowPxSize);

	// Init pathfinder
    Pathfinder  finder(TileCountHoriz, TileCountVert, tileSize);
	finder.getInfoBox().initInfoBox(window, windowPxSize, tileSize);

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

			// Add possibility to reset calculations by pressing R

			if (event.type == sf::Event::KeyPressed && finder.getState() == CLICKED)
				finder.checkClickedInput(event);
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
				finder.changeDisplayNumberState();

            if (event.type == sf::Event::MouseButtonPressed \
            && event.mouseButton.button == sf::Mouse::Button::Left)
                finder.checkMousePress(window);
        }

        window.clear();

		if (finder.getStartPos().x != -1 && finder.getFinishPos().x != -1)
		{
			finder.initAlgo(windowPxSize);
			finder.executeAlgo();
		}

		finder.drawGrid(window);
		finder.getInfoBox().draw(window, finder.getState()); // Make more abstract

		if (finder.getDisplayNumberStatus())
			finder.getAlgo().drawNumbers(window, tileSize);

	

        window.display();
    }
}


/*
	HELPER FUNCTION
*/

void    fixWindowPos(sf::RenderWindow &window, sf::Vector2u windowPxSize)
{
     // Get monitor size
    sf::Vector2i monitorSize;
    monitorSize.x = sf::VideoMode::getDesktopMode().width;
    monitorSize.y = sf::VideoMode::getDesktopMode().height;

/*	float	height = monitorSize.y * 0.8;

	if (height > windowPxSize.y)
	{
		sf::Vector2u	newSize;
		newSize.x = height;
		newSize.y = height;
		window.setSize(newSize);
	}
*/

    // Center monitor
    sf::Vector2i windowPos;
    windowPos.x = monitorSize.x / 2 - window.getSize().x / 2;
    windowPos.y = monitorSize.y / 2 - window.getSize().y / 2;
    window.setPosition(windowPos);

}


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