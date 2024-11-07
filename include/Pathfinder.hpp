#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

# include <iostream>
# include <vector>

# include "InfoBox.hpp"
# include "FinderAlgo.hpp"


class Pathfinder
{
    private:

	InfoBox		info;
	FinderAlgo	algo;

    const float     m_tileSize;
    const int       m_gridWidth; // in pixels
    const int       m_gridHeight; // in pixels

    std::vector<std::vector<gridTile>>  m_gridVec;
    sf::RectangleShape  m_drawShape;

	sf::Vector2i	m_activeTile; // in tiles
	sf::Vector2i	m_startCoord; // in tiles
	sf::Vector2i	m_finishCoord; // in tiles

    int     m_state;
	bool	m_dislayNumbers;
	bool	m_algoInit;
	bool	m_algoFinished;

	void	initGridVec();
	void	updateTileInfo(int type, sf::Color color);

    /*************/

    public:

    Pathfinder(const int &width, const int &height, int &tileSize);
    ~Pathfinder() {};

    void    drawGrid(sf::RenderWindow &window);

	void	initAlgo(sf::Vector2u windowSize);
	void	executeAlgo();
	void	resetAlgo();

    void    checkMousePress(sf::RenderWindow &window);
	void	checkClickedInput(sf::Event &event);

	void	changeDisplayNumberState();

	InfoBox			&getInfoBox();
	FinderAlgo		&getAlgo();
	int				getState();
	bool			&getDisplayNumberStatus();
	sf::Vector2i	&getStartPos();
	sf::Vector2i	&getFinishPos();
	std::vector<std::vector<gridTile>>  &getGridVec();


};


#endif