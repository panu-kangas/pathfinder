#ifndef FINDERALGO_HPP
# define FINDERALGO_HPP

# include "Types.hpp"

class Pathfinder;


class FinderAlgo
{
	private:

	sf::Vector2i	m_startCoord; // const...?
	sf::Vector2i	m_finishCoord; // const...?
	sf::Font		m_font;
	sf::Text		m_distanceInfoText;
	std::vector<gridTile *>	m_adjacentTileVec;
	std::vector<gridTile *>	m_visitedTileVec;
	std::vector<gridTile *>	m_finalPath;

	bool			m_straightPathFoundX;

	void		visitTile(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord);
	gridTile	*checkAdjacentTiles(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord);
	void		countGridDistance(gridTile &tile);
	void		findFinalPath(std::vector<std::vector<gridTile>> &gridVec);
	bool		checkForStraightRouteX(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord);
	bool		isStartReached(std::vector<std::vector<gridTile>> &gridVec, sf::Vector2i coord);

//////

	public:

	FinderAlgo();
	~FinderAlgo() {};

	void	init(sf::Vector2i startPos, sf::Vector2i finishPos, sf::Vector2u windowSize);
	bool	execute(std::vector<std::vector<gridTile>> &gridVec);
	void	reset();

	void	drawNumbers(sf::RenderWindow &window, int &tileSize);

};

#endif