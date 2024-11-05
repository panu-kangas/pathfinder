#include "Pathfinder.hpp"

/*
    CONSTRUCTOR
*/

Pathfinder::Pathfinder(const int &width, const int &height, const int &tileSize) : 
m_gridWidth(width * tileSize), m_gridHeight(height * tileSize), m_tileSize(tileSize)
{
    // Init grid vector
    gridTile    tempTile;
    std::vector<gridTile>   tempVec;

	tempTile.distToStart = 0;
	tempTile.distToFinish = 0;

    for (int y = 0; y < m_gridHeight; y += m_tileSize)
    {
        for (int x = 0; x < m_gridWidth; x += m_tileSize)
        {
            if (y == m_gridHeight - m_tileSize) // the last row
            {
                tempTile.type = INFO;
                tempTile.color = sf::Color{208, 206, 199};
            }
            else
            {
                tempTile.type = EMPTY;
                tempTile.color = sf::Color::White;
            }
			tempTile.coord.x = x;
			tempTile.coord.y = y;
			
            tempVec.push_back(tempTile);
        }
        m_gridVec.push_back(tempVec);
        tempVec.clear();
    }

    m_drawShape.setSize({m_tileSize, m_tileSize});
    m_drawShape.setOutlineThickness(2);
    m_drawShape.setOutlineColor(sf::Color::Black);

    m_state = FREE;

	m_activeTile.x = 0;
	m_activeTile.y = 0;
	m_startCoord.x = -1;
	m_startCoord.y = -1;
	m_finishCoord.x = -1;
	m_finishCoord.y = -1;
}


/*
    DRAW GRID
*/

void    Pathfinder::drawGrid(sf::RenderWindow &window)
{
    for (float y = 0; y < m_gridHeight; y += m_tileSize)
    {
        for (float x = 0; x < m_gridWidth; x += m_tileSize)
        {
            m_drawShape.setFillColor(m_gridVec[y / m_tileSize][x / m_tileSize].color);
            m_drawShape.setPosition(x, y);
            if (m_gridVec[y / m_tileSize][x / m_tileSize].type == INFO)
            {
                m_drawShape.setOutlineThickness(0);
                window.draw(m_drawShape);
                m_drawShape.setOutlineThickness(2);
            }
            else
                window.draw(m_drawShape);
        }
    }
}


/*
    INPUT HANDLING
*/

void    Pathfinder::checkMousePress(sf::RenderWindow &window)
{
    sf::Vector2i    mousePos = sf::Mouse::getPosition(window);

    m_activeTile.x = mousePos.x / m_tileSize;
    m_activeTile.y = mousePos.y / m_tileSize;

	if (m_gridVec[m_activeTile.y][m_activeTile.x].type == INFO)
		return ;

	std::string	infoText;
	std::string tileText;

	infoText = "You can change the tile type with the following keys:\nW = Wall, E = Empty, S = Start, F = Finish";
	tileText = "Tile coordinate:\nx = " + std::to_string(m_activeTile.x) \
	+ ", y = " + std::to_string(m_activeTile.y);

	info.setInfoText(infoText, tileText);

	if (m_state == FREE)
		m_state = CLICKED;
}

void	Pathfinder::checkClickedInput(sf::Event &event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::W :
			updateTileInfo(WALL, sf::Color::Black);
			break ;
		
		case sf::Keyboard::E :
			updateTileInfo(EMPTY, sf::Color::White);
			break ;

		case sf::Keyboard::S :
			updateTileInfo(START, sf::Color::Green);
			break ;
		
		case sf::Keyboard::F :
			updateTileInfo(FINISH, sf::Color::Blue);
			break ;

		default:
			break ;
	}
}

void	Pathfinder::updateTileInfo(int type, sf::Color color)
{
	// Allow only one start/finish
	if (type == START)
	{
		if (m_startCoord.x >= 0)
		{
			m_gridVec[m_startCoord.y][m_startCoord.x].type = EMPTY;
			m_gridVec[m_startCoord.y][m_startCoord.x].color = sf::Color::White;
		}
		m_startCoord.x = m_activeTile.x;
		m_startCoord.y = m_activeTile.y;
	}
	else if (type == FINISH)
	{
		if (m_finishCoord.x >= 0)
		{
			m_gridVec[m_finishCoord.y][m_finishCoord.x].type = EMPTY;
			m_gridVec[m_finishCoord.y][m_finishCoord.x].color = sf::Color::White;
		}
		m_finishCoord.x = m_activeTile.x;
		m_finishCoord.y = m_activeTile.y;
	}

	// If start/finish is overwritten, init coords
	if (m_gridVec[m_activeTile.y][m_activeTile.x].type == START \
	&& type != START)
	{
		m_startCoord.x = -1;
		m_startCoord.y = -1;
	}
	else if (m_gridVec[m_activeTile.y][m_activeTile.x].type == FINISH \
	&& type != FINISH)
	{
		m_finishCoord.x = -1;
		m_finishCoord.y = -1;
	}

	// Update info
	m_gridVec[m_activeTile.y][m_activeTile.x].type = type;
	m_gridVec[m_activeTile.y][m_activeTile.x].color = color;
	m_state = FREE;
}



/*
	GETTERS
*/

InfoBox	&Pathfinder::getInfoBox()
{
	return (info);
}

int		Pathfinder::getState()
{
	return (m_state);
}

sf::Vector2i	&Pathfinder::getStartPos()
{
	return (m_startCoord);
}

sf::Vector2i	&Pathfinder::getFinishPos()
{
	return (m_finishCoord);
}


std::vector<std::vector<gridTile>>  &Pathfinder::getGridVec()
{
	return (m_gridVec);
}


