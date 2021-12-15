#include <random>

#include "game.h"

#include "iostream"

#pragma region CONSTRUCTOR

Game::Game() :
	m_gravity(0.0f, -.981f),
	m_world(m_gravity),
	m_character(*this),
	m_contacts(*this),
	m_trailManager(m_world)
{
	//MUSIC
	m_music.openFromFile("data/music/space.wav");
	m_music.setVolume(25);
	m_music.setLoop(true);
	
	//SOUND
	m_bufferThruster.loadFromFile("data/sound/thruster.wav");
	m_bufferCrash.loadFromFile("data/sound/crash.wav");
	
	//TEXT - Font
	m_font.loadFromFile("data/font/RetroGaming.ttf");
	//TEXT - Score
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(80); // in pixels, not points!
	m_scoreText.setFillColor(sf::Color::Red);
	//TEXT - Life
	m_lifeText.setFont(m_font);
	m_lifeText.setCharacterSize(80);
	m_lifeText.setFillColor(sf::Color::Red);
	
}

#pragma endregion
#pragma region GAME METHODS
void Game::Init() 
{
	TextureManager* texture_manager = TextureManager::Instance();

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 generator(rd()); // seed the generator
	std::uniform_real_distribution<> rndPos(-1.0f, 1.0f); // define the range
	std::uniform_real_distribution<> rndAngle(-1.0f, 1.0f); // define the range

#pragma region Window

	m_window.create(sf::VideoMode(1280, 1024), "ToTheMoonAndBack");
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60.0f);
	
#pragma endregion
#pragma region WindowLimits

	// Set Boudaries (Game&, Position, Size)
	// Top Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, 0.0f),
			sf::Vector2f(m_window.getSize().x, 10.0f), 
			false));
	// Bottom Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.5f * m_window.getSize().x, m_window.getSize().y),
			sf::Vector2f(m_window.getSize().x, 10.0f),
			true));
	// Left Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(0.0f, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y),
			false));
	// Right Boundary
	m_boundaries.push_back(
		Boundary(
			*this,
			sf::Vector2f(m_window.getSize().x, 0.5f * m_window.getSize().y),
			sf::Vector2f(10.0f, m_window.getSize().y),
			false));

#pragma endregion
#pragma region BackGroundElements

	for (int star = 0; star < 100; star++) 
	{
		float scale = rndPos(generator);
		m_stars.push_back(
			Star(*this,
				sf::Vector2f(m_window.getSize().x * rndPos(generator), m_window.getSize().y * rndPos(generator)),
				sf::Vector2f(scale, scale),
				rndAngle(generator)));
	}

#pragma endregion
#pragma region GameElements

	m_world.SetContactListener(&m_contacts);

	m_character.Init(m_window.getSize());
	m_character.move(sf::Vector2f(0.5f * m_window.getSize().x, 0.5f * m_window.getSize().y));

#pragma endregion
#pragma region UiElements

	m_scoreText.setPosition(sf::Vector2f(m_window.getSize().x * 0.025f, 0));
	m_lifeText.setPosition(sf::Vector2f(m_window.getSize().x * 0.7f, 0));

#pragma endregion

}
void Game::Loop()
{
		//Music
		m_music.play();

	while (m_window.isOpen())
	{
		//Game Timer used for the Score
		sf::Time elapsed = m_scoreClock.restart();
		m_scoreTime += elapsed;
		m_score = m_scoreTime.asSeconds();
		
		
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
				m_character.Move(b2Vec2(0.0f, 100.0f));

				//Set alpha to max
				m_character.MaxThrusterAlphaValue();

				//play sound
				m_sound1.setBuffer(m_bufferThruster);
				m_sound1.play();
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				//Move Left
				m_character.Move(b2Vec2(-100.0f, 0.0f));
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				//Move Right
				m_character.Move(b2Vec2(100.0f, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				//Move Down
				m_character.Move(b2Vec2(0.0f, -20.0f));
			}
		}

#pragma endregion
#pragma region Physical process
		if(!m_gameOver)
		{
			// Updating the world with a delay
			float timeStep = 1.0f / 60.0f;
			int32 velocityIterations = 6;
			int32 positionIterations = 2;
			m_world.Step(timeStep, velocityIterations, positionIterations);

			std::random_device rd; // obtain a random number from hardware
			std::mt19937 generator(rd()); // seed the generator
			std::uniform_real_distribution<> rndPos(-1.0f, 1.0f); // define the range
		
			//Updating Elements
			//Character
			m_character.Update();
			for (auto& boundaries : m_boundaries) 
			{
				boundaries.Update();
			}
			//Stars (BackGround)
			for (auto& star : m_stars)
			{
				star.Update();
				//std::cout << object.GetSprite().getPosition().y << std::endl;
				if (star.GetSprite().getPosition().y >= m_window.getSize().y)
				{
					star.GetSprite().setPosition(star.GetSprite().getPosition().x, 0.0f);
				}
			}

			// Tick every 5.0sec
			sf::Time elapsed = m_clock.restart();
			m_deltaTime += elapsed;
			
			if (m_deltaTime.asSeconds() > 0.5f) 
			{

				std::random_device rd; // obtain a random number from hardware
				std::mt19937 generator(rd()); // seed the generator
				std::uniform_int_distribution<> rndX(0, m_window.getSize().x); // define the range
				std::uniform_int_distribution<> rndY(0, m_window.getSize().y); // define the range

				sf::Vector2f rndPos((rndX(generator)), pixelsToMeters(0.0f));
				//test pos
				sf::Vector2f testPos(10, 0.0f);
				std::cout << rndPos.x << "\n";
				// Pop Trail
				m_trailManager.AddTrail(rndPos);

				m_deltaTime = sf::Time::Zero;
			}

			//Trails
			m_trailManager.Update();

			if (m_character.GetHealth() <= 0) 
			{
				m_gameOver = true;
				return;
			}
		}
#pragma endregion
#pragma region Graphical process

		sf::Time elapsedTime = m_clock2.restart();
		m_deltaTime2 += elapsedTime;

		sf::Color fullColor = sf::Color(255, 255, 255, 255);
		if (m_deltaTime2.asSeconds() > 0.25f) 
		{
			m_deltaTime2 = sf::Time::Zero;
			if (m_character.GetMainSprite().getColor() == sf::Color::Red)
			{
				m_character.ResetColor();
			}
		}
		
		m_character.LowerThrusterAlphaValue();

		// Clear all background
#pragma region DRAW

		m_window.clear();
		// Render All elements
		//Draw Boundaries
		for (auto& boundary : m_boundaries) 
		{
			m_window.draw(boundary);
		}

		for (auto& star : m_stars) 
		{
			m_window.draw(star);
		}
		//Draw Character
		m_window.draw(m_character);
		//Draw Trails
		m_window.draw(m_trailManager);
		//Draw Text
		m_scoreText.setString("Score: " + std::to_string((int)m_score));
		m_window.draw(m_scoreText);
		m_lifeText.setString("Life: " + std::to_string((int)m_character.GetHealth()));
		m_window.draw(m_lifeText);
		// Display all elements
		m_window.display();

#pragma endregion

#pragma endregion

	}
}
#pragma endregion

#pragma region ContactMethods

void Game::DestroyTrail(int trailId)
{
	m_trailManager.DestroyTrail(trailId);
}

void Game::SetDamageToRocket(float damage) 
{
	m_character.SetDamage(damage);
	m_deltaTime2 = sf::Time::Zero;
	m_sound2.setBuffer(m_bufferCrash);
	m_sound2.play();
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