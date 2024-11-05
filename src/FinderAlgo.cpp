#include "FinderAlgo.hpp"

/*
	CONSTRUCTOR
*/

FinderAlgo::FinderAlgo(sf::Vector2i &startPos, sf::Vector2i &finishPos)
{
	if (!m_font.loadFromFile("assets/Roboto-Black.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	m_distanceInfoText.setFont(m_font);
	m_distanceInfoText.setCharacterSize(10);

	m_startCoord = startPos;
	m_finishCoord = finishPos;
}

/*
	COUNTER
*/

// make this a singular check --> it takes in one gridTile and counts distances to it
void	FinderAlgo::countDistances(std::vector<std::vector<gridTile>> &gridVec)
{
	for (std::vector<gridTile> &vector : gridVec)
	{
		for (gridTile &tile : vector)
		{
			// Get tileSize here somehow
			tile.distToStart = abs(m_startCoord.x - tile.coord.x / 40) + abs(m_startCoord.y - tile.coord.y / 40);
			tile.distToFinish = abs(m_finishCoord.x - tile.coord.x / 40) + abs(m_finishCoord.y - tile.coord.y / 40);
		}
	}
}

/*
	DRAW
*/

void	FinderAlgo::draw(sf::RenderWindow &window, std::vector<std::vector<gridTile>> &gridVec)
{
	for (std::vector<gridTile> &vector : gridVec)
	{
		for (gridTile &tile : vector)
		{
			m_distanceInfoText.setFillColor(sf::Color::Black);
			m_distanceInfoText.setString(std::to_string(tile.distToStart));
			m_distanceInfoText.setPosition(tile.coord.x + 2, tile.coord.y + 2);
			window.draw(m_distanceInfoText);

			m_distanceInfoText.setFillColor(sf::Color::Blue);
			m_distanceInfoText.setString(std::to_string(tile.distToFinish));
			m_distanceInfoText.setPosition(tile.coord.x + 28, tile.coord.y + 2);
			window.draw(m_distanceInfoText);

			m_distanceInfoText.setFillColor(sf::Color::Red);
			m_distanceInfoText.setString(std::to_string(tile.distToStart + tile.distToFinish));
			m_distanceInfoText.setPosition(tile.coord.x + 15, tile.coord.y + 15);
			window.draw(m_distanceInfoText);

		}
	}
}


