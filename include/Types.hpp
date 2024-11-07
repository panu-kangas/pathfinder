#ifndef TYPES_HPP
# define TYPES_HPP

# include <SFML/Graphics.hpp>

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
    CLICKED,
	PATHREADY
};

struct  gridTile
{
	int         	type;
    sf::Color   	color;
	sf::Vector2i	coord;
	bool			isVisited;
	bool			isFinalPath;

	int				distToStart;
	int				distToFinish;
	int				distTotal;
};

#endif