#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Character : public sf::Drawable, public sf::Transformable
{
protected:
	//SMFL object
	//Ship
	sf::Sprite m_mainSprite;
	std::string m_mainSpriteAdress;
	sf::Texture m_mainTexture;
	//Thruster
	std::string m_secondSpriteAdress;
	sf::Texture m_secondTexture;

	
	//Box2D object
	b2Body* m_body = nullptr;

	Game& m_game;
	
public:

	//Thruster
	sf::Sprite m_secondSprite;
	float m_thrusterAlphaValue = 0;

#pragma region Ctors
	
	explicit Character(Game& game);

#pragma endregion
#pragma region Game Methods
	
	void Init(sf::Vector2u winsize);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Thruster(b2Vec2 b2Vec2);
	void MoveLeft(b2Vec2 force);
	void MoveRight(b2Vec2 force);

	void SetSpriteAlpha(sf::Sprite& sprite, float alphaValue);

#pragma endregion


};