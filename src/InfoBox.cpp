#include "InfoBox.hpp"
#include "Pathfinder.hpp"


/*
	CONSTRUCTOR
*/

InfoBox::InfoBox()
{
	if (!m_Font.loadFromFile("assets/Roboto-Black.ttf"))
	{
		std::cout << "\nError occurred while loading font.\nExiting program.\n" << std::endl;
		exit(1);
	}

}


/*
	INIT INFO
*/

void	InfoBox::initInfoBox(sf::RenderWindow &window, sf::Vector2u windowSize, const int &tileSize)
{
	m_boxPos.x = 0;
	m_boxPos.y = windowSize.y - tileSize;

	m_infoText.setFont(m_Font);
	m_infoText.setPosition(m_boxPos.x + 2, m_boxPos.y + 2);
	m_infoText.setCharacterSize(windowSize.x / 45); // Fix this later...?
	m_infoText.setFillColor(sf::Color::Black);

	m_tileText.setFont(m_Font);
	m_tileText.setCharacterSize(windowSize.x / 56); // Fix this later...?
	m_tileText.setFillColor(sf::Color::Black);
	m_tileText.setPosition(windowSize.x - windowSize.x / 7.8, m_boxPos.y + 2);
}


/*
	SET TEXT
*/

void	InfoBox::setInfoText(std::string infoText, std::string tileText)
{
	m_infoText.setString(infoText);
	m_tileText.setString(tileText);
}

/*
	DRAW
*/

void	InfoBox::draw(sf::RenderWindow &window, int state)
{
	if (state == FREE)
		setInfoText("Click one of the grid tiles to change their type", "");

	window.draw(m_infoText);
	window.draw(m_tileText);
}


