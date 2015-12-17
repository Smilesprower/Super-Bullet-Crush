#include "stdafx.h"
#include "BulletGroup.h"
#include "BulletManager.h"


BulletGroup::BulletGroup()
{



}


BulletGroup::~BulletGroup()
{
}

void BulletGroup::Update(sf::Time p_deltaTime, sf::Vector2f p_screenDimensions)
{
	m_hasDestroyedAMissile = sf::Vector2f(-1, -1);

	for (int i = 0; i < m_bulletList.size(); i++)
	{
		if (m_bulletList.at(i).m_shouldBeDestroyed)
		{
			m_hasDestroyedAMissile = m_bulletList.at(i).GetPosition();
			// Need to take in a value for how many bullets are in the explody pattern
			// I have coded the explosion to work with every number you throw at it.
			BulletManager::Instance().AddExplosion(m_bulletList.at(i).GetPosition(), 24, m_bulletList.at(i).GetVelocity());
			m_bulletList.erase(m_bulletList.begin() + i);
		}
	}
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		m_bulletList.at(i).Update(p_deltaTime);
		if (m_bulletList.at(i).GetPosition().x > p_screenDimensions.x || m_bulletList.at(i).GetPosition().x < -m_bulletRadius ||
			m_bulletList.at(i).GetPosition().y > p_screenDimensions.y || m_bulletList.at(i).GetPosition().y < -m_bulletRadius)
		{
			m_bulletList.erase(m_bulletList.begin() + i);
		}

	}
}

float BulletGroup::GetRadius()
{
	return m_bulletRadius;
}

bool BulletGroup::ShouldBeDestroyed()
{
	return (m_bulletList.size() == 0);
}

void BulletGroup::SetShouldBeDestroyed(bool p_shouldBeDestroyed)
{
	m_shouldBeDestroyed = true;
}

bool BulletGroup::GetShouldBeDestroyed()
{
	return m_shouldBeDestroyed;
}

sf::Vector2f BulletGroup::HasDestroyedAMissile()
{
	return m_hasDestroyedAMissile;
}
