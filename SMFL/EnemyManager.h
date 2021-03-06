#pragma once
#include <vector>
#include "Enemy.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "Boss.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	static EnemyManager& Instance();
	void Init(sf::Texture& p_tex);
	void Update(sf::Vector2f p_playerPos, float p_dt, sf::Vector2f p_screenDimensions, int p_levelNum);
	void Draw(sf::RenderWindow& p_window);
	std::vector<Enemy*> * GetEnemyList();
	Boss * GetBoss();
	bool ShouldCheckBoss();
	void Reset(int p_levelNum);
private:
	std::vector<Enemy*> m_enemyList;
	Boss m_boss;
	sf::Texture *m_textureAtlas;

	static const sf::IntRect m_HOMING_ENEM_COORDS;
	static const sf::IntRect m_SLOW_SHOOTY_ENEM_COORDS;
	static const sf::IntRect m_WAVE_ENEM_COORS;
	static const sf::IntRect m_BOSS_COORDS;

	void ManageEnemySpawning(sf::Vector2f p_screenDimensions, sf::Vector2f p_playerPos, float p_dt, int p_levelNum);

	void AddHomingEnem(sf::Vector2f p_position);
	void AddSlowShootyEnem(sf::Vector2f p_position);
	void AddWaveyEnem(sf::Vector2f p_position);

	void AddHomingWave(sf::Vector2f p_screenDimensions);
	void AddWaveyWave(sf::Vector2f p_screenDimensions);
	void AddSlowWave(sf::Vector2f p_screenDimensions);

	//Enemy timer shit
	const float m_TIME_BETWEEN_HOMING_WAVES = 200;
	const float m_TIME_BETWEEN_HOMING_WAVES_LVL2 = 600;
	const float m_TIME_BETWEEN_SLOW_WAVES = 700;
	const float m_TIME_BETWEEN_SLOW_WAVES_LVL2 = 10000;
	const float m_TIME_BETWEEN_WAVE_WAVES = 60;
	const float m_TIME_BETWEEN_WAVE_WAVES_LVL2 = 10;

	const float m_MAX_WAVES = 100;
	const float m_MAX_WAVES_LVL2 = 200;

	const float m_SAFETY_TIME = 9000000;
	float m_safteyCounter = 0;

	float m_homingWaveTimer = 0;
	float m_slowWaveTimer = 0;
	float m_waveWaveTimer = 0;
	int m_waveCounter = m_MAX_WAVES;
};
