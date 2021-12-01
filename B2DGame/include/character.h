#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Character
{
private:
	//Root game;
	Game& m_game;
	//SMFL object
	sf::ConvexShape m_shape;
	//SFML window
	sf::RenderWindow& m_window;
	//Box2D object
	b2Body* m_body = nullptr;
public:

#pragma region Ctor
	
	Character(Game& game, sf::RenderWindow& window);

#pragma endregion
#pragma region Game Methods
	
	void Init();
	void Update();
	void Render();
	void SetPixelsPosition(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

#pragma endregion


};