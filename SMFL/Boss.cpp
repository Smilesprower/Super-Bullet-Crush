#include "stdafx.h"
#include "Boss.h"

const sf::Vector2f Boss::m_END_POS = sf::Vector2f(350, 100);
const sf::Vector2f Boss::m_START_POS = sf::Vector2f(75, -350);

const sf::Vector2f Boss::m_TOWER_POS_1 = sf::Vector2f(177, -250);
const sf::Vector2f Boss::m_TOWER_POS_2 = sf::Vector2f(287, -175);
const sf::Vector2f Boss::m_TOWER_POS_3 = sf::Vector2f(402, -250);

const sf::IntRect Boss::m_TOWER_COLL_BOX_1 = sf::IntRect(77, -520, 200, 200);
const sf::IntRect Boss::m_TOWER_COLL_BOX_2 = sf::IntRect(250, -370, 100, 200);
const sf::IntRect Boss::m_TOWER_COLL_BOX_3 = sf::IntRect(322, -520, 200, 200);

const sf::IntRect Boss::m_TOWER_TEX_RECT = sf::IntRect(98, 126, 28, 28);

const sf::IntRect Boss::m_BOSS_SIZE = sf::IntRect(50, 50, 400, 100);

const float Boss::m_DEATHANIMTIMER = 60000;
const float Boss::m_MAXEXPFRAMES = 7;
const int Boss::m_NUM_EXPLOSIONS = 5;


const int Boss::m_EXPSIZE = 40;
const int Boss::m_TEXOFFSETY = 156;




Boss::Boss(sf::Texture * p_tex, sf::IntRect p_texRect)
{
	m_sprite = sf::Sprite(*p_tex);
	m_sprite.setTextureRect(p_texRect);

	m_position = m_START_POS;
	m_sprite.setPosition(m_START_POS);

	m_velocity = sf::Vector2f(0, 0.0001);

	m_animHasFinished = false;
	m_state = BossState::ALIVE;
	m_counterForAnim = 0;
	m_currentFrame = 0;

	m_towerList = std::vector<BossTower>();
	m_weakSpots = std::vector<WeakSpot>();
	m_explosionSprites = std::vector<Boss::ExplosionAnim>();

	for (int i = 0; i < m_NUM_EXPLOSIONS; i++)
	{
		ExplosionAnim tempexpl;
		sf::Sprite tempPushSpr = sf::Sprite(*p_tex);
		sf::IntRect newRect;
		newRect = sf::IntRect(m_EXPSIZE * m_currentFrame, m_TEXOFFSETY, m_EXPSIZE, m_EXPSIZE);
		tempPushSpr.setTextureRect(newRect);
		tempPushSpr.setScale(4, 4);
		tempexpl.my_position = sf::Vector2f(m_END_POS.x + ((rand() % 400) - 300), m_END_POS.y + (rand() % 100)); (m_position);
		tempexpl.my_sprite.setPosition(tempexpl.my_position);
		tempexpl.my_sprite = tempPushSpr;

		tempexpl.my_currentFrame = rand() % (int)(m_MAXEXPFRAMES);
		tempexpl.my_counterForAnim = (rand() % (int(m_DEATHANIMTIMER)));

		m_explosionSprites.push_back(tempexpl);
	}

	m_towerList.push_back(BossTower(m_TOWER_POS_1, p_tex, m_TOWER_TEX_RECT, m_TOWER_COLL_BOX_1));
	m_towerList.push_back(BossTower(m_TOWER_POS_2, p_tex, m_TOWER_TEX_RECT, m_TOWER_COLL_BOX_2));
	m_towerList.push_back(BossTower(m_TOWER_POS_3, p_tex, m_TOWER_TEX_RECT, m_TOWER_COLL_BOX_3));

}

Boss::Boss()
{

}


Boss::~Boss()
{
}

void Boss::Update(sf::Vector2f p_playerPos, float p_dt)
{
	if (m_position.y < m_END_POS.y)
	{
		m_position += m_velocity * p_dt;
		for (int i = 0; i < m_towerList.size(); i++)
		{
			m_towerList.at(i).UpdatePosition(m_velocity * p_dt);
		}
	}

	m_sprite.setPosition(m_position);

	for (int i = 0; i < m_towerList.size(); i++)
	{
		m_towerList.at(i).Update(p_playerPos, p_dt);
	}

	switch (m_state)
	{
	case BossState::ALIVE:
		break;
	case BossState::PLAYING_ANIM:

		for (int i = 0; i < m_explosionSprites.size(); i++)
		{
			m_explosionSprites.at(i).UpdateAnim(p_dt);
		}

		break;
	case BossState::DEAD:
		break;

	}

}

void Boss::Init()
{

}

std::vector<sf::Sprite> Boss::GetTextureList()
{
	std::vector<sf::Sprite> spriteList;

	if (m_state == BossState::ALIVE)
	{
		spriteList.push_back(m_sprite);

		for (int i = 0; i < m_towerList.size(); i++)
		{
			spriteList.push_back(*m_towerList.at(i).GetTexture());
		}
		for (int i = 0; i < m_weakSpots.size(); i++)
		{
			spriteList.push_back(*m_weakSpots.at(i).GetTexture());
		}
	}
	else
	{
		spriteList.push_back(m_sprite);
		for (int i = 0; i < m_NUM_EXPLOSIONS; i++)
		{
			spriteList.push_back(m_explosionSprites.at(i).my_sprite);
		}
	}
	

	return spriteList;
}

std::vector<BossTower> * Boss::GetTowerList()
{
	return &m_towerList;
}

bool Boss::CheckIfDefeated()
{
	bool isDefeated = true;
	for (int i = 0; i < m_towerList.size(); i++)
	{
		if (m_towerList.at(i).GetAliveState() != Enemy::IS_DEAD)
		{
			isDefeated = false;
		}
	}

	if (m_state == BossState::ALIVE && isDefeated)
	{
		m_state = BossState::PLAYING_ANIM;
		isDefeated = false;
	}
	else if (m_state == BossState::PLAYING_ANIM)
	{
		isDefeated = false;
	}
	else if (m_state == BossState::DEAD)
	{
		isDefeated = true;
	}


	return isDefeated;
}

bool Boss::CheckIfBossHasStopped()
{
	return (m_position.y >= m_END_POS.y);
}

bool Boss::CheckIfExploding()
{
	return (m_state == PLAYING_ANIM);
}
