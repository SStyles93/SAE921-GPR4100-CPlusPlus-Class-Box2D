#include "game.h"

#pragma region Ctor

Game::Game() :
	m_gravity(0.0f, -.981f),
	m_world(m_gravity),
	m_character(*this)
{}

#pragma endregion
#pragma region Game Methods

void Game::Init() 
{
#pragma region Window

	m_window.create(sf::VideoMode(1280, 1024), "ToTheMoonAndBack");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);

#pragma endregion
#pragma region WindowLimits

	// Set Boudaries
	// Top Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, 0.0f),
			sf::Vector2f(m_window.getSize().x, 10.0f)));
	// Bottom Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, m_window.getSize().y),
			sf::Vector2f(m_window.getSize().x, 10.0f)));
	// Left Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.0f, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y)));
	// Right Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(m_window.getSize().x, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y)));

#pragma endregion
#pragma region BackGroundElements


	// Background elements
	m_objects.push_back(
		Object(*this, 
			sf::Vector2f(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f),
			sf::Vector2f(20.0f, 20.0f),
			"data/sprites/star.png"));
	m_objects.push_back(
		Object(*this, 
			sf::Vector2f(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f),
			sf::Vector2f(20.0f, 20.0f),
			"data/sprites/trail.png"));

#pragma endregion
#pragma region GameElements

	m_character.Init(m_window.getSize());
	m_character.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y));

#pragma endregion

}
void Game::Loop()
{

	while (m_window.isOpen())
	{

#pragma region Event processes
		sf::Event event;

		m_window.setKeyRepeatEnabled(false);

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				//Add Thrust
				m_character.Thruster(b2Vec2(0.0f, 100.0f));
				//Set alpha to max
				m_character.SetSpriteAlpha(m_character.m_secondSprite, m_character.m_thrusterAlphaValue = 255.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				//TODO : Move Left
				m_character.MoveLeft(b2Vec2(-100.0f, 0.0f));
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				//TODO: Move Right
				m_character.MoveRight(b2Vec2(100.0f, 0.0f));
			}
			
		}

#pragma region Physical process

		// Updating the world with a delay
		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		m_world.Step(timeStep, velocityIterations, positionIterations);
		
		//Updating Elements
		m_character.Update();
		for (auto& boundaries : m_boundaries) 
		{
			boundaries.Update();
		}
		for (auto& object : m_objects) 
		{
			object.Update();
		}

#pragma endregion
#pragma region Graphical process

		//Lowers the Thruster alpha
		if (m_character.m_thrusterAlphaValue >= 0.0f)
		{
			m_character.SetSpriteAlpha(m_character.m_secondSprite, m_character.m_thrusterAlphaValue -= m_character.m_thrusterAlphaValue / 10);
		}

		// Clear all background
		m_window.clear();
		// Render All elements
		m_window.draw(m_character);
		for (auto& boundary : m_boundaries) 
		{
			m_window.draw(boundary);
		}
		for (auto& object : m_objects)
		{
			m_window.draw(object);
		}
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