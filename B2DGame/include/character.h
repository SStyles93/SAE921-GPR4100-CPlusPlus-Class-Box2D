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
	sf::Texture m_mainTexture;
	std::string m_mainSpriteAdress;
	sf::Sprite m_mainSprite;
	//Thruster
	sf::Texture m_secondTexture;
	std::string m_secondSpriteAdress;
	sf::Sprite m_secondSprite;
	float m_thrusterAlphaValue = 0;

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

	

#pragma region CONSTRUCTOR
	
	explicit Character(Game& game);

#pragma endregion
#pragma region GETTER/SETTER

	sf::Sprite GetMainSprite() {return m_mainSprite; };
	sf::Sprite SetMainSprite(sf::Sprite sprite) { m_mainSprite = sprite; };
	sf::Sprite GetSecondSprite() { return m_secondSprite; };
	sf::Sprite SetSecondSprite(sf::Sprite sprite) { m_secondSprite = sprite; };
	float GetThrusterAlphaValue() { return m_thrusterAlphaValue; };

#pragma endregion

#pragma region GAME METHODS
	
	void Init(sf::Vector2u winsize);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Move(b2Vec2 b2Vec2);

	void SetSpriteAlpha(sf::Sprite& sprite, float alphaValue);
	//void SetSpriteColorR(sf::Sprite& sprite, float alphaValue);
	//void SetSpriteColorG(sf::Sprite& sprite, float alphaValue);
	//void SetSpriteColorB(sf::Sprite& sprite, float alphaValue);
	void MaxThrusterAlphaValue();
	void LowerThrusterAlphaValue();
	void ResetColor();

	void SetDamage(float damage);
	float GetHealth();

#pragma endregion

};