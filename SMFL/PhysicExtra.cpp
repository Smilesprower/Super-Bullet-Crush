#include "stdafx.h"
#include "PhysicExtra.h"
#include <iostream>

PhysicExtra::PhysicExtra()
{
}

PhysicExtra::PhysicExtra(sf::Vector2f p_pos, float p_size, sf::Vector2f p_vel, sf::Texture &p_tex) :
m_position(p_pos),
m_size(p_size),
m_update(false),
m_velocity(p_vel)
{
	m_ball.setPosition(m_position);
	m_ball.setRadius(p_size);
	m_ball.setOrigin(sf::Vector2f(22, 22));
	m_ball.setTexture(&p_tex);
	m_ball.setTextureRect(sf::IntRect(67, 112, 22, 22));
	myPI = 3.141592f;

}


PhysicExtra::~PhysicExtra()
{
}

sf::CircleShape PhysicExtra::GetShape()
{
	return m_ball;
}

void PhysicExtra::Update(float p_deltaTime)
{
	sf::Vector2f gravity = sf::Vector2f(0, 9.81 * 185);

	m_position.x += p_deltaTime* m_velocity.x + 0.5f * gravity.x *p_deltaTime * p_deltaTime;
	m_position.y += p_deltaTime * m_velocity.y + 0.5f * gravity.y * p_deltaTime * p_deltaTime;

	m_velocity.x += gravity.x * p_deltaTime;
	m_velocity.y += gravity.y * p_deltaTime;

	float angle = atan2(m_velocity.y, m_velocity.x) * 57.2958;
	m_ball.setRotation(angle * 2);


	m_ball.setPosition(m_position);
}
//void Ball::SetPosition(sf::Vector2f p_pos)
//{
//	m_position = p_pos;
//	m_ball.setPosition(m_position);
//}

sf::Vector2f PhysicExtra::GetPosition()
{
	return m_position;
}


sf::Vector2f PhysicExtra::GetVelocity()
{
	return m_velocity;
}

void PhysicExtra::SetVel(sf::Vector2f p_vel)
{
	m_velocity = p_vel;
}

void PhysicExtra::SetPos(sf::Vector2f p_pos)
{
	m_position = p_pos;
}
