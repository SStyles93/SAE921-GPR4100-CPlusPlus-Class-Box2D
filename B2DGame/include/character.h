#pragma once

#include "UserData.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Character : public sf::Drawable, public sf::Transformable
{
protected:

#pragma region SMFL

	//Ship
	sf::Sprite m_mainSprite;
	std::string m_mainSpriteAdress;
	sf::Texture m_mainTexture;
	//Thruster
	std::string m_secondSpriteAdress;
	sf::Texture m_secondTexture;

#pragma endregion
#pragma region BOX2D

	b2Body* m_body = nullptr;
	Game& m_game;
	UserData* m_userData = new UserData(UserDataType::ROCKET);

#pragma endregion
#pragma region CHARACTERISTICS

	//Life 
	float m_health = 100;

#pragma endregion
	
public:

	//Thruster
	sf::Sprite m_secondSprite;
	float m_thrusterAlphaValue = 0;

#pragma region CONSTRUCTOR
	
	explicit Character(Game& game);

#pragma endregion
#pragma region GAME METHODS
	
	void Init(sf::Vector2u winsize);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void SetSpriteAlpha(sf::Sprite& sprite, float alphaValue);


	void Thruster(b2Vec2 b2Vec2);
	void MoveLeft(b2Vec2 force);
	void MoveRight(b2Vec2 force);

	void SetDamage(float damage);
	float GetHealth();

#pragma endregion

};