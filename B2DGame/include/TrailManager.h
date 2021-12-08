#pragma once

#include <vector>

#include <box2d/b2_world.h>
#include "SFML/Graphics/Drawable.hpp"

#include "Trail.h"

class TrailManager : public sf::Drawable
{

private:
	std::vector<Trail> m_trails;
	b2World& m_world;

public:
	TrailManager(b2World& world);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update();

	void AddTrail(sf::Vector2f startPos, float angle);
	void DestroyTrail(int trailId);

};