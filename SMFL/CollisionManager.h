#pragma once
#include "stdafx.h"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\System\Vector2.hpp"
#include "Player.h"
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();


	void Init();

	static CollisionManager& Instance();

	void CheckCollisions(sf::IntRect p_playerPos, Player * p_player);
	void CheckBossCollisions(sf::IntRect p_playerPos);
	void EnemBulletPl(Player * p_player);
private:
	void PlBulletEnemy();
};

