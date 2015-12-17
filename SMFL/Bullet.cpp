#include "stdafx.h"
#include "Bullet.h"


const float Bullet::m_RADTODEG = 180 / acos(-1);
const float Bullet::m_MAX_TIME_TO_LIVE = 1200000;

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Vector2f p_position, sf::Vector2f p_velocity, sf::Texture *&p_tex, sf::IntRect p_texCoords, int p_radius, Bullet::BulletType p_type)
{
	m_type = p_type;
	m_position = p_position;
	m_velocity = p_velocity;

	m_currentTimeLeft = m_MAX_TIME_TO_LIVE;

	m_sprite.setTexture(*p_tex);
	m_sprite.setTextureRect(p_texCoords);
	m_sprite.setPosition(m_position);

	m_radius = p_radius;

	m_sprite.setOrigin(m_radius, m_radius);
	m_position += m_sprite.getOrigin();

	m_sprite.setRotation(atan2(m_velocity.y, m_velocity.x) * m_RADTODEG + 90);
	m_shouldBeDestroyed = false;

}


Bullet::~Bullet()
{
}

sf::Sprite * Bullet::GetTexture()
{
	return &m_sprite;
}

void Bullet::Update(sf::Time p_deltaTime)
{
	m_position += sf::Vector2f(m_velocity.x * p_deltaTime.asSeconds() * 100, m_velocity.y * p_deltaTime.asSeconds() * 100);
	m_sprite.setPosition(m_position);

	if (m_type == BulletType::MISSILE)
	{
		m_currentTimeLeft -= p_deltaTime.asMicroseconds();
		if (m_currentTimeLeft < 0)
		{
			m_shouldBeDestroyed = true;
		}
	}

	m_collisionRect = sf::IntRect(m_position.x - m_radius, m_position.y - m_radius, m_radius * 2, m_radius * 2);
}

sf::Vector2f Bullet::GetPosition()
{
	return m_position;
}

sf::IntRect Bullet::GetCollisionRect()
{
	return m_collisionRect;
}

void Bullet::SetPosition(sf::Vector2f p_pos)
{
	m_position = p_pos;
}

Bullet::BulletType Bullet::GetType()
{
	return m_type;
}

sf::Vector2f Bullet::GetVelocity()
{
	return m_velocity;
}

