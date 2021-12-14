#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "box2d/b2_world.h"

#include "character.h"
#include "boundary.h"
#include "object.h"
#include "star.h"
#include "trail.h"
#include "TextureManager.h"
#include "ContactListener.h"
#include "TrailManager.h"


class Game {

private:

	// Physical
	b2Vec2 m_gravity;
	b2World m_world;

	//Window
	sf::RenderWindow m_window;

	//Character
	Character m_character;
	
	//Boundaries
	std::vector<Boundary> m_boundaries;
	std::vector<Star> m_stars;
	TrailManager m_trailManager;
	ContactListener m_contacts;

	//Time Values
	sf::Clock m_clock;
	sf::Time m_deltaTime;

	bool m_gameOver = false;

public:

#pragma region CONSTRUCTOR

	Game();
	
#pragma endregion
#pragma region GAME METHODS
	
	void Init();
	void Loop();

	void SetDamageToRocket(float damages);
	void DestroyTrail(int idTrail);

#pragma endregion
#pragma region GETTER/SETTER

	b2World& GetWorld() { return m_world; }; 

#pragma endregion
#pragma region CONVERSION METHODS

	static b2Vec2 pixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 pixelsToMeters(sf::Vector2u pixels);
	static float pixelsToMeters(float pixels);
	static sf::Vector2f metersToPixels(b2Vec2 meters);
	static const float pixelsMetersRatio;

#pragma endregion

};