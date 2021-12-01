#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"


class Game {

private:

	// The window ---------------------------------------------
	sf::RenderWindow m_window;

	// The physical world -------------------------------------
	b2Vec2 m_gravity;
	b2World m_world;

public:

#pragma region Ctor

	Game();
	
#pragma endregion
#pragma region Game Methods
	
	void init();
	void loop();

#pragma endregion
#pragma region Getter/Setter

	b2World& getWorld() { return m_world; };

#pragma endregion
#pragma region Conversion Methods

	static b2Vec2 pixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 pixelsToMeters(sf::Vector2u pixels);
	static float pixelsToMeters(float pixels);
	static sf::Vector2f metersToPixels(b2Vec2 meters);
	static const float pixelsMetersRatio;

#pragma endregion

};