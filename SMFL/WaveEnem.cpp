#include "stdafx.h"
#include "WaveEnem.h"

const float WaveEnem::m_ACCEL = 0.000001;
const float WaveEnem::m_MAX_SPEED = 0.0005;
const float WaveEnem::m_COLLISIONBOXSIZE = 56;



WaveEnem::WaveEnem(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect, bool p_isGoingRight)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_health = 10;
	if (p_isGoingRight)
		m_state = WaveEnem::MovingState::GOING_LEFT;
	else
		m_state = WaveEnem::MovingState::GOING_RIGHT;

}


WaveEnem::~WaveEnem()
{
}

void WaveEnem::Init()
{
}

void WaveEnem::Update(sf::Vector2f p_playerPos, float p_dt)
{
	m_sinCounter += p_dt / 450000;
	if(m_state == WaveEnem::MovingState::GOING_LEFT)
		m_position.x = 275 + (sin(m_sinCounter) * 140);
	else
		m_position.x = 275 + (-sin(m_sinCounter) * 140);


	if (m_velocity.y < m_MAX_SPEED * 3)
		m_velocity.y += m_ACCEL;

	m_position += m_velocity * p_dt;
	m_sprite.setPosition(m_position);
	m_collisionBox = sf::IntRect(m_position.x + 24, m_position.y, 58, 50);
}