#include "FinderAlgo.hpp"
#include "Pathfinder.hpp"

/*
	CONSTRUCTOR
*/

FinderAlgo::FinderAlgo()
{
	if (!m_font.loadFromFile("assets/Roboto-Black.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

	m_distanceInfoText.setFont(m_font);
	m_straightPathFoundX = false;
}

/*
	INIT
*/

void	FinderAlgo::init(sf::Vector2i startPos, sf::Vector2i finishPos, sf::Vector2u windowSize)
{
	m_startCoord = startPos;
	m_finishCoord = finishPos;

	m_distanceInfoText.setCharacterSize(windowSize.x / 68); // Fix this later...?

}

/*
	EXECUTE
*/


bool	FinderAlgo::execute(std::vector<std::vector<gridTile>> &gridVec)
{
	if (m_straightPathFoundX)
	{
		findFinalPath(gridVec);
		m_straightPathFoundX = false;
		// other flag reset ?
		return (true);
	}
	else if (m_visitedTileVec.empty())
	{
		visitTile(gridVec, m_startCoord);
		return (false);
	}
	
	gridTile	*tileToVisitPTR = nullptr;
	int			smallestTotal = -1;

	for (gridTile *tilePTR : m_adjacentTileVec)
	{
		if (tilePTR->type == FINISH)
		{
			findFinalPath(gridVec);
			return (true);
		}

		if (tilePTR->isVisited == true)
			continue ;
		else if (smallestTotal == -1 || tilePTR->distTotal < smallestTotal)
		{
			tileToVisitPTR = tilePTR;
			smallestTotal = tilePTR->distTotal;
		}
		else if (tilePTR->distTotal == smallestTotal)
		{
			if (tilePTR->distToFinish < tileToVisitPTR->distToFinish)
				tileToVisitPTR = tilePTR;
		}
	}

	if (tileToVisitPTR != nullptr)
		visitTile(gridVec, tileToVisitPTR->coord);
	else
	{
		// Add a flag that changes the infobox message to: no path found
		std::cout << "Not path found!\n";
		
		return (true);
	}

	return (false);
}

void	FinderAlgo::visitTile(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord)
{
	m_visitedTileVec.push_back(&gridVec[coord.y][coord.x]);
	gridVec[coord.y][coord.x].isVisited = true;
	if (gridVec[coord.y][coord.x].type != START)
		gridVec[coord.y][coord.x].color = sf::Color::Yellow;

	if (coord.y > 0)
		countGridDistance(gridVec[coord.y - 1][coord.x]);
	if (coord.y < gridVec.size() - 1)
		countGridDistance(gridVec[coord.y + 1][coord.x]);
	if (coord.x > 0)
		countGridDistance(gridVec[coord.y][coord.x - 1]);
	if (coord.x < gridVec[coord.y].size() - 1)
		countGridDistance(gridVec[coord.y][coord.x + 1]);

	if (checkForStraightRouteX(gridVec, coord))
	{
		m_straightPathFoundX = true;
		return ;
	}
	// Do I also need checkForStraightRouteY()...?
	// It looks like no; the algo prefers up/down directions, so it finds it's way better on the y-axis
}

/*
	STRAIGHT PATH CHECKING
*/

bool	FinderAlgo::checkForStraightRouteX(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord)
{
	gridTile	*tempTilePTR = &gridVec[coord.y][coord.x];
	int			increment;
	bool		finishOnSameAxis = false;
	std::vector<gridTile *>	routeVec;

	// Set increment for the upcoming loop
	if (tempTilePTR->coord.x < m_finishCoord.x)
		increment = 1;
	else if (tempTilePTR->coord.x > m_finishCoord.x)
		increment = -1;
	if (tempTilePTR->coord.x == m_finishCoord.x)
		finishOnSameAxis = true;

	// Move through x-axis searching for FINISH (or same x position as FINISH)
	while (tempTilePTR->type != WALL && !finishOnSameAxis)
	{
		tempTilePTR = &gridVec[tempTilePTR->coord.y][tempTilePTR->coord.x + increment];
		if (tempTilePTR->type == FINISH)
			break ;
		routeVec.push_back(tempTilePTR);
		if (tempTilePTR->coord.x == m_finishCoord.x)
			break ;
	}

	if (tempTilePTR->type == WALL)
		return (false);
	else if (tempTilePTR->type == FINISH)
	{
		for (gridTile *routeTile : routeVec)
		{
			m_visitedTileVec.push_back(routeTile);
			routeTile->isVisited = true;
			if (routeTile->type != START)
				routeTile->color = sf::Color::Yellow;
		}
		return (true);
	}
	
	// Update increment for y-axis check
	if (tempTilePTR->coord.y < m_finishCoord.y)
		increment = 1;
	else if (tempTilePTR->coord.y > m_finishCoord.y)
		increment = -1;

	// Move through y-axis searching for FINISH
	while (tempTilePTR->type != WALL)
	{
		tempTilePTR = &gridVec[tempTilePTR->coord.y + increment][tempTilePTR->coord.x];
		if (tempTilePTR->type == FINISH)
			break ;
		routeVec.push_back(tempTilePTR);
	}

	if (tempTilePTR->type == FINISH)
	{
		for (gridTile *routeTile : routeVec)
		{
			m_visitedTileVec.push_back(routeTile);
			routeTile->isVisited = true;
			if (routeTile->type != START)
				routeTile->color = sf::Color::Yellow;
		}
		return (true);
	}

	return (false);
}

/*
	DISTANCE COUNTER
*/

void	FinderAlgo::countGridDistance(gridTile &tile)
{
	if (tile.type == WALL || tile.type == INFO
	|| tile.distToStart != 0)
		return ;

	tile.distToStart = abs(m_startCoord.x - tile.coord.x) + abs(m_startCoord.y - tile.coord.y);
	tile.distToFinish = abs(m_finishCoord.x - tile.coord.x) + abs(m_finishCoord.y - tile.coord.y);
	tile.distTotal = tile.distToStart + tile.distToFinish;

	m_adjacentTileVec.push_back(&tile);
}


/*
	FINAL PATH
*/

void	FinderAlgo::findFinalPath(std::vector<std::vector<gridTile>> &gridVec)
{
	gridTile		*pathTile;
	sf::Vector2i	curCoord = m_finishCoord;

	while (1)
	{
		pathTile = checkAdjacentTiles(gridVec, curCoord);
		if (pathTile == nullptr)
		{
			if (isStartReached(gridVec, curCoord))
				break ;
	
			pathTile = m_finalPath.back();
			pathTile->isDeadEnd = true;
			m_finalPath.pop_back();
			pathTile = m_finalPath.back();
		}
		else
		{
			pathTile->isFinalPath = true;
			m_finalPath.push_back(pathTile);
		}
		curCoord = pathTile->coord;
	}

	for (gridTile *tile : m_finalPath)
		tile->color = sf::Color{188, 220, 191};
}

bool		FinderAlgo::isStartReached(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord)
{
	int	x = coord.x;
	int y = coord.y;

	if (x < gridVec[y].size() - 1 && gridVec[y][x + 1].type == START)
		return (true);
	else if (x > 0 && gridVec[y][x - 1].type == START)
		return (true);
	else if (y < gridVec.size() - 1 && gridVec[y + 1][x].type == START)
		return (true);
	else if (y > 0 && gridVec[y - 1][x].type == START)
		return (true);

	return (false);
}


gridTile	*FinderAlgo::checkAdjacentTiles(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord)
{
	int				smallestTotal = -1;
	gridTile		*finalTile = nullptr;
	sf::Vector2i	origCoord = coord;

	for (int i = 0; i < 4; ++i)
	{
		coord = origCoord;
		if (i == 0 && coord.x > 0)
			coord.x -= 1;
		else if (i == 1 && coord.x < gridVec[coord.y].size() - 1)
			coord.x += 1;
		else if (i == 2 && coord.y > 0)
			coord.y -= 1;
		else if (i == 3 && coord.y < gridVec.size() - 1)
			coord.y += 1;

		gridTile &checkTile = gridVec[coord.y][coord.x];

		if (checkTile.type == START)
			return (nullptr);

		if (checkTile.isVisited == true && checkTile.isFinalPath == false && checkTile.isDeadEnd == false)
		{
			if (smallestTotal == -1 || checkTile.distTotal < smallestTotal)
			{
				finalTile = &checkTile;
				smallestTotal = checkTile.distTotal;
			}
			else if (checkTile.distTotal == smallestTotal)
			{
				if (checkTile.distToStart < finalTile->distToStart)
				{
					finalTile = &checkTile;
					smallestTotal = checkTile.distTotal;
				}
			}
		}
	}

	return (finalTile);
}



/*
	RESET
*/


void	FinderAlgo::reset()
{
	for (gridTile *tilePTR : m_adjacentTileVec)
	{
		tilePTR->distToStart = 0;
		tilePTR->distToFinish = 0;
		tilePTR->distTotal = 0;
	}
	m_adjacentTileVec.clear();
	for (gridTile *tilePTR : m_visitedTileVec)
	{
		tilePTR->distToStart = 0;
		tilePTR->distToFinish = 0;
		tilePTR->distTotal = 0;
		tilePTR->isVisited = false;
		tilePTR->isFinalPath = false;
		tilePTR->isDeadEnd = false;
		if (tilePTR->type != START && tilePTR->type != WALL)
			tilePTR->color = sf::Color::White;
	}
	m_visitedTileVec.clear();
	m_finalPath.clear();
}

/*
	DRAW
*/

void	FinderAlgo::drawNumbers(sf::RenderWindow &window, int &tileSize)
{
	for (gridTile *tilePTR : m_adjacentTileVec)
	{
		m_distanceInfoText.setFillColor(sf::Color{64, 131, 68});
		m_distanceInfoText.setString(std::to_string(tilePTR->distToStart));
		m_distanceInfoText.setPosition(tilePTR->coord.x * tileSize + 2, tilePTR->coord.y * tileSize + 2);
		window.draw(m_distanceInfoText);

		m_distanceInfoText.setFillColor(sf::Color::Blue);
		m_distanceInfoText.setString(std::to_string(tilePTR->distToFinish));
		m_distanceInfoText.setPosition(tilePTR->coord.x * tileSize + (tileSize / 1.6), tilePTR->coord.y * tileSize + 2);
		window.draw(m_distanceInfoText);

		m_distanceInfoText.setFillColor(sf::Color::Black);
		m_distanceInfoText.setString(std::to_string(tilePTR->distTotal));
		m_distanceInfoText.setPosition(tilePTR->coord.x * tileSize + (tileSize / 3), tilePTR->coord.y * tileSize + (tileSize / 2.6));
		window.draw(m_distanceInfoText);
	}


}


