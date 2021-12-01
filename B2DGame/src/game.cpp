#include "game.h"

#pragma region Ctor

Game::Game() :
	//Add a character
	m_gravity(0, -9.81f),
	m_world(m_gravity)
{

}

#pragma endregion
#pragma region Game Methods

void Game::init() 
{
	m_window.create(sf::VideoMode(1920, 1080), "ToTheMoonAndBack");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

	// Init all elements
}
void Game::loop()
{
	while (m_window.isOpen())
	{

#pragma region Event processes
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = m_window.getView();
				view.setSize(event.size.width, event.size.height);
				m_window.setView(view);
			}

			// Keyboard events
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) 
				{
					//TODO: Add Thrust	
				}
				if (event.key.code == sf::Keyboard::A) 
				{
					//TODO : Move Left
				}
				if (event.key.code == sf::Keyboard::D) 
				{
					//TODO: Move Right
				}
			}
		}
#pragma endregion
#pragma region Physical process

		// Updating the world with a delay
		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		m_world.Step(timeStep, velocityIterations, positionIterations);

		// Update the elements


#pragma endregion
#pragma region Graphical process

		// Clear all background
		m_window.clear();
		// Render All elements
		
		// Display all elements
		m_window.display();
		
#pragma endregion
	
	}
}

#pragma endregion
#pragma region Conversion Methods

//pixelsToMeters(from Vector2float)
b2Vec2 Game::pixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}
//pixelsToMeters(from Vector2unsigned)
b2Vec2 Game::pixelsToMeters(sf::Vector2u pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}
//pixelsToMeters(from float)
float Game::pixelsToMeters(float pixels)
{
	return pixels / pixelsMetersRatio;
}
//metersToPixels(from meters to vector2Float)
sf::Vector2f Game::metersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * pixelsMetersRatio, -1.0f * meters.y * pixelsMetersRatio);
}
//pixelsMetersRation definition
const float Game::pixelsMetersRatio = 100.0f;

#pragma endregion