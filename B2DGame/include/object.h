#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Object : public sf::Drawable, public sf::Transformable
{
protected:

#pragma region SMFL

	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

#pragma endregion
#pragma region BOX2D

	//B2D
	b2Body* m_body = nullptr;

#pragma endregion

public:

#pragma region GETTER/SETTER

	sf::Sprite& GetSprite() { return m_sprite; };

#pragma endregion
#pragma region GAME METHODS

	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

#pragma endregion

};
 
