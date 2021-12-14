#include "TrailManager.h"

#include "SFML/Graphics/Drawable.hpp"
#include "iostream"

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
	auto trail = std::remove_if(
		m_trails.begin(),
		m_trails.end(),
		[](Trail& trail) {return trail.GetIsDead(); });
	
	m_trails.erase(trail, m_trails.end());
	
	for (auto& trail : m_trails) 
	{
		trail.Update();
	}
}

void TrailManager::AddTrail(sf::Vector2f startPos)
{

	m_trails.emplace_back(
		Trail(
			m_world,
			startPos));
}

void TrailManager::DestroyTrail(int trailId)
{
	// Check id, then put isDead to true
	auto trail = std::find_if
	(m_trails.begin(),m_trails.end(),[trailId](Trail& trail) {return trail.GetLocalId() == trailId; });

	if (trail != m_trails.end())
	{
		trail->SetIsDead();
	}


}



