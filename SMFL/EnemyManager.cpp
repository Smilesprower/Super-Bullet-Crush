#include "stdafx.h"
#include "EnemyManager.h"
#include "HomingEnemy.h"
#include "SlowShootyEnem.h"
#include "Boss.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SFML\Graphics\RectangleShape.hpp"
#include "WaveEnem.h"

bool hasHomingSpawned = false;

const sf::IntRect EnemyManager::m_HOMING_ENEM_COORDS = sf::IntRect(0, 409, 60, 64);
const sf::IntRect EnemyManager::m_SLOW_SHOOTY_ENEM_COORDS = sf::IntRect(460, 8, 68, 59);
const sf::IntRect EnemyManager::m_WAVE_ENEM_COORS = sf::IntRect(0, 301, 62, 53);
const sf::IntRect EnemyManager::m_BOSS_COORDS = sf::IntRect(102, 299, 450, 224);

int counter = 0;
bool isGoingRight = (counter % 2);

bool shouldStartSpawning = false;

EnemyManager::EnemyManager()
{
	std::srand(std::time(0));
	m_enemyList = std::vector<Enemy*>();
}


EnemyManager::~EnemyManager()
{
	m_enemyList.clear();
}

EnemyManager& EnemyManager::Instance()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::Init(sf::Texture& p_tex)
{
	m_textureAtlas = &p_tex;
	m_boss = Boss(m_textureAtlas, m_BOSS_COORDS);
}

void EnemyManager::Update(sf::Vector2f p_playerPos, float p_dt, sf::Vector2f p_screenDimensions, int p_levelNum)
{
	isGoingRight = (counter % 2);

	ManageEnemySpawning(p_screenDimensions, p_playerPos, p_dt, p_levelNum);

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		if (m_enemyList.at(i)->CheckOffScreen(p_screenDimensions))
		{
			m_enemyList.at(i)->RemoveVars();
			m_enemyList.erase(m_enemyList.begin() + i);
		}
	}

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList.at(i)->Update(p_playerPos, p_dt);
		if (m_enemyList.at(i)->UpdateAnim(p_dt) == false)
		{
			m_enemyList.at(i)->RemoveVars();
			m_enemyList.erase(m_enemyList.begin() + i);
		}
	}


	if (m_waveCounter == 0) // if in the boss mode
	{
		for (int i = 0; i < m_boss.GetTowerList()->size(); i++)
		{
			if (m_boss.GetTowerList()->at(i).UpdateAnim(p_dt) == false)
				m_boss.GetTowerList()->erase(m_boss.GetTowerList()->begin() + i);
		}
		m_boss.Update(p_playerPos, p_dt);
		if (m_boss.CheckIfDefeated())
		{
			m_waveCounter = 5;
			m_boss = Boss(m_textureAtlas, m_BOSS_COORDS);
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow& p_window)
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		p_window.draw(*m_enemyList.at(i)->GetTexture());
	}

	std::vector<sf::Sprite> bossSprites = m_boss.GetTextureList();
	for (int i = 0; i < bossSprites.size(); i++)
	{
		p_window.draw(bossSprites.at(i));
	}


}

void EnemyManager::AddHomingEnem(sf::Vector2f p_position)
{
	m_enemyList.push_back(new HomingEnemy(p_position, m_textureAtlas, m_HOMING_ENEM_COORDS));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}


void EnemyManager::AddWaveyEnem(sf::Vector2f p_position)
{
	m_enemyList.push_back(new WaveEnem(p_position, m_textureAtlas, m_WAVE_ENEM_COORS, isGoingRight));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}

std::vector<Enemy*> * EnemyManager::GetEnemyList()
{
	return &m_enemyList;
}

void EnemyManager::AddSlowShootyEnem(sf::Vector2f p_position)
{
	m_enemyList.push_back(new SlowShootyEnem(p_position, m_textureAtlas, m_SLOW_SHOOTY_ENEM_COORDS));
	m_enemyList.at(m_enemyList.size() - 1)->Init();
}

void EnemyManager::AddHomingWave(sf::Vector2f p_screenDimensions)
{

	m_homingWaveTimer = 0;
	m_waveCounter--;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			AddHomingEnem(sf::Vector2f(0 + (i * 100), -100 - (j * 50)));
		}
	}
	
}

void EnemyManager::AddSlowWave(sf::Vector2f p_screenDimensions)
{
	m_slowWaveTimer = 0;
	m_waveCounter--;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			int xPos = int(std::rand() % (int)p_screenDimensions.x);
			AddSlowShootyEnem(sf::Vector2f(sf::Vector2f(xPos, -100 - (j * 50))));
		}
	}
	
}

void EnemyManager::AddWaveyWave(sf::Vector2f p_screenDimensions)
{

	counter++;
	m_waveWaveTimer = 0;
	m_waveCounter--;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			int xPos = 500;
			AddWaveyEnem(sf::Vector2f(sf::Vector2f(xPos, -100 - (j * 50))));
		}
	}
	
}


void EnemyManager::ManageEnemySpawning(sf::Vector2f p_screenDimensions, sf::Vector2f p_playerPos, float p_dt, int p_levelNum)
{
	if (p_levelNum % 2 == 0)
	{
		if (shouldStartSpawning)
		{
			m_homingWaveTimer += p_dt / 10000;
			m_slowWaveTimer += p_dt / 10000;
			m_waveWaveTimer += p_dt / 10000;
		}
		else
		{
			m_safteyCounter += p_dt;
			if (m_safteyCounter > m_SAFETY_TIME)
				shouldStartSpawning = true;
		}

		if (m_waveCounter != 0)
		{
			if (m_waveWaveTimer > m_TIME_BETWEEN_WAVE_WAVES)
				AddWaveyWave(p_screenDimensions);

			if (m_slowWaveTimer > m_TIME_BETWEEN_SLOW_WAVES)
				AddSlowWave(p_screenDimensions);

			if (m_homingWaveTimer > m_TIME_BETWEEN_HOMING_WAVES)
				AddHomingWave(p_screenDimensions);
		}
	}
	else
	{
		if (shouldStartSpawning)
		{
			m_homingWaveTimer += p_dt / 10000;
			m_slowWaveTimer += p_dt / 10000;
			m_waveWaveTimer += p_dt / 10000;
		}
		else
		{
			m_safteyCounter += p_dt;
			if (m_safteyCounter > m_SAFETY_TIME)
				shouldStartSpawning = true;
		}

		if (m_waveCounter != 0)
		{
			if (m_waveWaveTimer > m_TIME_BETWEEN_WAVE_WAVES_LVL2)
				AddWaveyWave(p_screenDimensions);

			if (m_slowWaveTimer > m_TIME_BETWEEN_SLOW_WAVES_LVL2)
				AddSlowWave(p_screenDimensions);

			if (m_homingWaveTimer > m_TIME_BETWEEN_HOMING_WAVES_LVL2)
				AddHomingWave(p_screenDimensions);
		}
	}

	
}

Boss * EnemyManager::GetBoss()
{
	return &m_boss;
}

bool EnemyManager::ShouldCheckBoss()
{
	return (m_waveCounter == 0);
}

void EnemyManager::Reset(int p_levelNum)
{
	m_enemyList.clear();
	if (p_levelNum % 2 == 0)
		m_waveCounter = m_MAX_WAVES;
	else
		m_waveCounter = m_MAX_WAVES_LVL2;

	m_waveWaveTimer = 0;
	m_slowWaveTimer = 0;
	m_homingWaveTimer = 0;

	m_safteyCounter = 0;
	shouldStartSpawning = false;

	m_boss = Boss(m_textureAtlas, m_BOSS_COORDS);
}