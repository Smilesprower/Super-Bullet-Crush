#pragma once
#include "Enemy.h"
class WaveEnem : public Enemy
{
public:
	WaveEnem(sf::Vector2f p_position, sf::Texture * p_tex, sf::IntRect p_texRect, bool p_isGoingRight);
	~WaveEnem();
	void Init();
	void Update(sf::Vector2f p_playerPos, float p_dt);
	void RemoveVars(){};	
	
	enum MovingState
	{
		GOING_LEFT,
		GOING_RIGHT
	};

private:
	static const float m_ACCEL;
	static const float m_COLLISIONBOXSIZE;
	static const float m_MAX_SPEED;
	float m_sinCounter = 0;



	MovingState m_state;

};

