#pragma once

#include "UserData.h"
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

	UserData* m_userData = new UserData(UserDataType::ROCKET);

	//Life 
	float m_health = 100;
	
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
	void SetSpriteAlpha(sf::Sprite& sprite, float alphaValue);


	void Thruster(b2Vec2 b2Vec2);
	void MoveLeft(b2Vec2 force);
	void MoveRight(b2Vec2 force);

	void SetDamage(float damage);
	float GetHealth();

#pragma endregion


};