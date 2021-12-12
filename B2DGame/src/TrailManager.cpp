#include "TrailManager.h"

#include "SFML/Graphics/Drawable.hpp"

TrailManager::TrailManager(b2World& world_) : m_world(world_)
{

}

void TrailManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& m : m_trails) {
		target.draw(m, states);
	}
}

void TrailManager::Update()
{
	auto a = std::remove_if(
		m_trails.begin(),
		m_trails.end(),
		[](Trail& a) {return a.getIsDead(); });

	m_trails.erase(a, m_trails.end());

	for (auto& aa : m_trails) {
		aa.Update();
	}
}

void TrailManager::AddTrail(sf::Vector2f startPos)
{

	m_trails.emplace_back(
		Trail(
			m_world,
			startPos)
	);
}

void TrailManager::DestroyTrail(int trailId)
{
	// Check id, then put isDead to true
	auto a = std::find_if(
		m_trails.begin(),
		m_trails.end(),
		[trailId](Trail& a) {return a.getLocalId() == trailId; }
	);

	if (a != m_trails.end())
	{
		a->setIsDead();
	}


}



