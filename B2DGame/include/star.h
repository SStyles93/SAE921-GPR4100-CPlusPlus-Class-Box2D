#pragma once

#include "UserData.h"
#include "object.h"

class Game;

class Star : public sf::Drawable, public sf::Transformable
{
public:

#pragma region GETTER/SETTER

	sf::Sprite& GetSprite() { return m_sprite; };

#pragma endregion
#pragma region CONSTRUCTOR

	Star(Game& game, sf::Vector2f pos, sf::Vector2f scale, float angle);

#pragma endregion
#pragma region GAME METHODS

	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

#pragma endregion

protected:
	//Root
	Game& m_game;

#pragma region SMFL

	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

#pragma endregion
#pragma region BOX2D

	//B2D
	b2Body* m_body = nullptr;

#pragma endregion

};