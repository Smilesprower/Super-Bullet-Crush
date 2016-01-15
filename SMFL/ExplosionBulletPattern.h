#pragma once
#include "BulletGroup.h"

class ExplosionBulletPattern : public BulletGroup
{
public:
	ExplosionBulletPattern(sf::Vector2f p_position, int p_numColumns, int p_radius, float p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords, sf::Vector2f p_direction, bool p_isPlayer);
	~ExplosionBulletPattern();

private:
	int m_columnCount = 12;
	float m_velocity;
};

