#pragma once

#include "UserData.h"
#include "object.h"

class Game;

class Star : public sf::Drawable, public sf::Transformable
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

	explicit Star(Game& game, sf::Vector2f pos, sf::Vector2f scale, float angle);
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};