#ifndef INFOBOX_HPP
# define INFOBOX_HPP

# include <iostream>
# include <SFML/Graphics.hpp>

class Pathfinder;


class InfoBox
{
	private:

	sf::Font	m_Font;
	sf::Text	m_infoText;
	sf::Text	m_tileText;

	sf::Vector2f	m_boxPos;

	/*********/

	public:

	InfoBox ();
	~InfoBox() {};

	void	initInfoBox(sf::RenderWindow &window, const int &tileSize);
	void	draw(sf::RenderWindow &window, int state);

	void	setInfoText(std::string text, std::string tileText);

};


#endif