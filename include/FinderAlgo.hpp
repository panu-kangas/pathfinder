#ifndef FINDERALGO_HPP
# define FINDERALGO_HPP

# include "Pathfinder.hpp"

class FinderAlgo
{
	private:

	sf::Vector2i	m_startCoord; // const...?
	sf::Vector2i	m_finishCoord; // const...?

	sf::Font		m_font;
	sf::Text		m_distanceInfoText;


	public:

	FinderAlgo(sf::Vector2i &startPos, sf::Vector2i &finishPos);
	~FinderAlgo() {};

	void	countDistances(std::vector<std::vector<gridTile>> &gridVec);
	void	draw(sf::RenderWindow &window, std::vector<std::vector<gridTile>> &gridVec);

};

#endif