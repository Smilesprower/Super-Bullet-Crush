#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Joystick.hpp"
#include "BulletGroup.h"
#include "StraightBulletGroup.h"
#include "PlControls.h"
#include "Tower.h"
#include "BulletManager.h"
#include "SoundManager.h"

#pragma once

class Player
{
public:
	// Default Constructor
	Player();
	// Destructor
	~Player();
	// Overloaded Constructor
	Player(sf::Texture&, sf::Vector2f p_pos);


	void Update(float p_deltaTime);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	std::vector<sf::Sprite> getSprite();
	void Shoot(int);

	sf::IntRect GetCollisionBox();

	enum AliveState
	{
		ALIVE,
		DEAD,
		PLAYING_ANIM,
		INVUNRABLE,
	};

	void SetAliveState(AliveState p_state);
	int GetLivesNum();
	bool CheckIfInvulnerable();
	bool CheckIfHidden();
	AliveState GetAliveState();
	void Setlives(int);
private:

	void UpdateAlive(float p_dt);
	void UpdateDead(float p_dt);
	void UpdateAnim(float p_dt);



	BulletManager::WeaponType m_weaponType;

	float m_angle, m_radiusForAngle;
	float m_delay, m_counterForHeliAnim;

	int m_lives;
	static const int m_MAX_LIVES;
	AliveState m_aliveState;

	sf::Vector2f m_position, m_origin, m_velocity;
	sf::Vector2f m_bulletVel;

	int m_currentFrame;
	int m_bulletGroupIndex;


	std::vector<Tower> m_towers;
	std::vector<sf::Sprite> m_allSprites;
	///////////////////////////////////

	sf::Texture * m_tex;
	sf::IntRect m_spriteRect;
	sf::Sprite m_playerSprite;
	sf::Sprite m_wepSel;
	StraightBulletGroup * m_pBulletlist;
	StraightBulletGroup m_bulletList;
	sf::IntRect m_collisionRect;

	bool m_isInvulnerable;
	static const int m_INVULNERABLE_LENGTH;
	float m_invulnerableCounter;
	int m_flashCounter;
	static const int m_FLASH_TIMER;
	bool m_shouldBeHidden;


	// Jay was here tested shtuff
	//////////////////////////////////////
	bool m_changePos;
	int m_noOfExp;

	static const int m_DEATHANIMTIMER;
	float m_counterFordeathAnim;
	static const int m_MAXEXPFRAMES;
	sf::IntRect m_animBox;
	static const int m_EXPSIZEX;
	static const int m_EXPSIZEY;
	static const int m_LEFTBORDER, m_RIGHTBORDER, m_TOPBORDER, m_BOTTOMBORDER;
	static const int m_TEXOFFSETY;
	static const int m_TEXOFFSETX;
	static const float m_COLLISIONBOXWIDTH;
	static const float m_COLLISIONBOXHEIGHT;
	static const float m_ANIMTIMER, m_SPREADDELAYTIMER, m_MISSILEDELAYTIMER, m_BLASTERDELAYTIMER ;
	static const float m_SPEED, m_BULLETSPEED, m_MISSILE_BULLETSPEED;
	static const int m_WIDTH, m_HEIGHT, m_MAXFRAMES, m_MAXTOWERS;
	static const float m_DEGTORAD, m_SPREADANGLE;
	static const int m_BLASTERRADIUS, m_SPREADRADIUS, m_LAZERRADIUS, m_MISSILERADIUS;
};
