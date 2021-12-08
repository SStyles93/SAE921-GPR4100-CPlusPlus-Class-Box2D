#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Object : public sf::Drawable, public sf::Transformable
{
private:
	//Root
	Game& m_game;

	//Star
	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

	sf::RectangleShape m_shape;

	//B2D
	b2Body* m_body = nullptr;

public:

	explicit Object(Game& game, sf::Vector2f pos, float angle);
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
 
