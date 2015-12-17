#include "stdafx.h"
#include "ExplosionBulletPattern.h"
#define _USE_MATH_DEFINES
#include <math.h>

float theDistFormula(sf::Vector2f x, sf::Vector2f y)
{
	float distance, tempx, tempy;
	tempx = (x.x - y.x);
	tempx = pow(tempx, 2.0f);
	tempy = (x.y - y.y);
	tempy = pow(tempy, 2.0f);
	distance = tempx + tempy;
	distance = sqrt(distance);
	return distance;
}

ExplosionBulletPattern::ExplosionBulletPattern(sf::Vector2f p_position, int p_numColumns, int p_radius, float p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords, sf::Vector2f p_direction)
:m_velocity(p_velocity)
{
	float deg2rad = (acos(-1) / 180);
	m_bulletList = std::vector<Bullet>();
	m_position = p_position;
	m_bulletRadius = p_radius;
	m_shouldBeDestroyed = true;
	float angle = atan2(p_direction.x, - p_direction.y);

	for (int i = 0; i < m_columnCount / 2; i++)
	{
		float currAng = (i * M_PI * 2 / m_columnCount) - 165 * deg2rad;
		currAng += angle;
		sf::Vector2f pointOnCircle = sf::Vector2f(cos(currAng), sin(currAng));
		sf::Vector2f velDir = pointOnCircle;



		sf::Vector2f vel = velDir * m_velocity;
		pointOnCircle = sf::Vector2f(cos(currAng) * m_bulletRadius + m_position.x, sin(currAng) * m_bulletRadius + m_position.y);
		m_bulletList.push_back(Bullet(pointOnCircle, vel, p_tex, p_texCoords));
	}
}


ExplosionBulletPattern::~ExplosionBulletPattern()
{
}
