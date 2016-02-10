#include "stdafx.h"
#include "Level.h"



Level::Level()
{
}

Level::Level(std::vector<sf::Texture>& p_levelTextures, sf::Vector2f p_screenDimensions):
m_tex(&p_levelTextures),
m_screenDimensions(p_screenDimensions),
m_bgRect(sf::IntRect(0,0,p_screenDimensions.x, p_screenDimensions.y * 0.5)),
m_positionOne(sf::Vector2f(0,-p_screenDimensions.y)),
m_bgY(400)
{
	m_bgSprite.setScale(sf::Vector2f(2, 4));
	m_bgSprite.setTexture(m_tex->at(0));
	m_bgSprite.setTextureRect(m_bgRect);
	m_bgSprite.setPosition(sf::Vector2f(0, 0));

	m_alpha = 0;
	m_endLevelSprite.setPosition(-50, -50);
	m_endLevelSprite.setSize(sf::Vector2f(p_screenDimensions.x + 100, p_screenDimensions.y +100));
	m_endLevelSprite.setFillColor(sf::Color(0, 0, 0, m_alpha));
}


Level::~Level()
{
}

void Level::Update(float p_deltaTime, bool p_bossStopped, bool p_bossDead)
{
	if (!p_bossStopped)
	{
		m_bgY -= p_deltaTime * 30;
		if (m_bgY <= 0)
			m_bgY = m_screenDimensions.y * 0.5f;
		m_bgSprite.setTextureRect(sf::IntRect(0, m_bgY, m_screenDimensions.x, m_screenDimensions.y));
	}
	if (p_bossDead)
	{
		m_alpha += p_deltaTime * 20;
		if (m_alpha < 255)
			m_endLevelSprite.setFillColor(sf::Color(0, 0, 0, m_alpha));
	}
}

void Level::ChangeLevel(int p_level)
{
	m_currentLevel = p_level;
}

sf::Sprite Level::getSprite()
{
	return m_bgSprite;
}

sf::RectangleShape Level::getEndLevelImage()
{
	return m_endLevelSprite;
}

int Level::GetLevelCount()
{
	return m_currentLevel;
}
