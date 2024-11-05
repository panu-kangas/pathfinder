#ifndef PATHFINDER_HPP
# define PATHFINDER_HPP

# include <iostream>
# include <vector>

# include "InfoBox.hpp"

enum gridtypes
{
    EMPTY,
    WALL,
    START,
    FINISH,
    INFO
};

enum states
{
    FREE = 10,
    CLICKED
};

struct  gridTile
{
    sf::Color   color;
    int         type;
};


class Pathfinder
{
    private:

	InfoBox		info;

    const float     m_tileSize;
    const int       m_gridWidth; // in pixels
    const int       m_gridHeight; // in pixels

    std::vector<std::vector<gridTile>>  m_gridVec;
    sf::RectangleShape  m_drawShape;

	sf::Vector2i	m_activeTile;
	sf::Vector2i	m_startCoord;
	sf::Vector2i	m_finishCoord;

    int     m_state;

	void	updateTileInfo(int type, sf::Color color);

    /*************/

    public:

    Pathfinder(const int &width, const int &height, const int &tileSize);
    ~Pathfinder() {};

    void    drawGrid(sf::RenderWindow &window);

    void    checkMousePress(sf::RenderWindow &window);
	void	checkClickedInput(sf::Event &event);

	InfoBox	&getInfoBox();
	int		getState();

};


#endif