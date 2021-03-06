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

#pragma region CONSTRUCTOR

	TrailManager(b2World& world);

#pragma endregion
#pragma region METHODS

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update();
	//MANAGER METHODS
	void AddTrail(sf::Vector2f startPos);
	void DestroyTrail(int trailId);

#pragma endregion

};