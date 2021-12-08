#pragma once

#include "object.h"

class Game;

class Trail : public sf::Drawable, public sf::Transformable
{
protected:
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

	sf::Sprite& GetSprite() { return m_sprite; };

	explicit Trail(Game& game, sf::Vector2f pos, float angle);
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};