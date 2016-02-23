#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Time.hpp"
#include "SFML/Graphics.hpp" 
class PhysicExtra
{
public:
	PhysicExtra();
	~PhysicExtra();
	PhysicExtra(sf::Vector2f p_pos, float p_size, sf::Vector2f p_vel, sf::Texture &p_tex);
	void PhysicExtra::Update(float p_deltaTime);

	sf::CircleShape PhysicExtra::GetShape();
	sf::Vector2f GetVelocity();
	sf::Vector2f GetPosition();
	void SetVel(sf::Vector2f);
	void SetPos(sf::Vector2f);
	bool m_update;


private:
	sf::Vector2f m_position, m_velocity;
	float m_angle, m_speed, m_size;
	sf::CircleShape m_ball;
	float myPI;
};
