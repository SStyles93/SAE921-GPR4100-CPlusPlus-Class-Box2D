#pragma once
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window//Event.hpp"
#include "SFML/Audio.hpp"
#include "box2d/b2_world.h"

#include "character.h"
#include "boundary.h"
#include "object.h"
#include "star.h"
#include "trail.h"
#include "Managers/textureManager.h"
#include "Managers/contactListener.h"
#include "Managers/trailManager.h"


class Game {

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

private:

#pragma region Physical

	// Physical
	b2Vec2 m_gravity;
	b2World m_world;

	//Boundaries
	std::vector<Boundary> m_boundaries;
	std::vector<Star> m_stars;
	TrailManager m_trailManager;
	ContactListener m_contacts;
	
	//Character
	Character m_character;

#pragma endregion
#pragma region Graphical

	//Window
	sf::RenderWindow m_window;

	//Time Values
	sf::Clock m_clock;
	sf::Time m_deltaTime;
	sf::Clock m_clock2;
	sf::Time m_deltaTime2;

	sf::Clock m_scoreClock;
	sf::Time m_scoreTime;
	float m_score = 0;

	//Music
	sf::Music m_music;
	//Sound
	sf::SoundBuffer m_bufferThruster;
	sf::SoundBuffer m_bufferCrash;
	sf::Sound m_soundThruster;
	sf::Sound m_soundCrash;

	//Text
	sf::Font m_font;
	sf::Text m_scoreText;
	sf::Text m_lifeText;

#pragma endregion

	bool m_gameOver = false;

};