#pragma once
#include "BossTower.h"
#include <vector>
#include "WeakSpot.h"
class Boss
{

	class ExplosionAnim
	{
	public:
		int my_EXPSIZE = 40;
		float my_counterForAnim;
		float my_currentFrame;

		sf::Sprite my_sprite;
		sf::Vector2f my_position;

		void UpdateAnim(float p_dt)
		{
			my_counterForAnim += p_dt;
			if (my_counterForAnim > m_DEATHANIMTIMER)
			{
				my_currentFrame++;
				my_counterForAnim = 0;
				if (my_currentFrame > m_MAXEXPFRAMES)
				{
					//m_state = BossState::DEAD;
					my_currentFrame = 0;
					my_position = sf::Vector2f(m_END_POS.x + ((rand() % 400) - 300), m_END_POS.y + (rand() % 100));
				}
				sf::IntRect newRect = sf::IntRect(my_EXPSIZE * my_currentFrame, m_TEXOFFSETY, my_EXPSIZE, my_EXPSIZE);
				my_sprite.setTextureRect(newRect);
				my_sprite.setScale(4, 4);
				my_sprite.setPosition(my_position);
			}
		}
	};

public:
	Boss();
	Boss(sf::Texture * p_tex, sf::IntRect p_texRect);
	~Boss();

	void Init();
	void Update(sf::Vector2f, float p_dt);
	void RemoveVars(){};
	std::vector<sf::Sprite> GetTextureList();
	std::vector<BossTower> * GetTowerList();
	bool CheckIfDefeated();
	bool CheckIfBossHasStopped();
	bool CheckIfExploding();

private:
	std::vector<BossTower> m_towerList;
	std::vector<WeakSpot> m_weakSpots;
	sf::Sprite m_sprite;
	std::vector<Boss::ExplosionAnim> m_explosionSprites;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	//////////////////////////////////////////////////////////////////////////
	//animation stuffs
	enum BossState
	{
		ALIVE,
		PLAYING_ANIM,
		DEAD
	};

	BossState m_state;
	bool m_animHasFinished;
	float m_counterForAnim;
	float m_currentFrame;

	static const int m_NUM_EXPLOSIONS;
	static const float m_DEATHANIMTIMER;
	static const float m_MAXEXPFRAMES;
	static const int m_EXPSIZE;
	static const int m_TEXOFFSETY;
	//////////////////////////////////////////////////////////////////////////

	static const sf::Vector2f m_END_POS;
	static const sf::Vector2f m_START_POS;

	static const sf::Vector2f m_TOWER_POS_1;
	static const sf::Vector2f m_TOWER_POS_2;
	static const sf::Vector2f m_TOWER_POS_3;

	static const sf::IntRect m_TOWER_COLL_BOX_1;
	static const sf::IntRect m_TOWER_COLL_BOX_2;
	static const sf::IntRect m_TOWER_COLL_BOX_3;

	static const sf::IntRect m_TOWER_TEX_RECT;

	static const sf::IntRect m_BOSS_SIZE;
};

