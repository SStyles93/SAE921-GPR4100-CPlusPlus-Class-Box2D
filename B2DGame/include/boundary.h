#pragma once

#include "UserData.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Boundary : public sf::Drawable, public sf::Transformable
{

private:
	// Root game
	Game& m_game;

	// Graphic object
	sf::RectangleShape m_shape;

	// The box 2D object
	b2Body* m_body = nullptr;

	UserData* m_userData = new UserData(UserDataType::NONE);

public:

	b2Body* getBody() { return m_body; };

	explicit Boundary(Game& game, sf::Vector2f pos, sf::Vector2f size, bool flag);

	void Init(sf::Vector2f, sf::Vector2f);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;



};