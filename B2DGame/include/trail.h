#pragma once

#include "Managers/userData.h"
#include "object.h"
#include "Managers/sfmlUtilities.h"

class Game;

class Trail : public sf::Drawable, public sf::Transformable
{
public:

	Trail(b2World& world, sf::Vector2f pos);

#pragma region GETTER/SETTER

	long GetLocalId();
	void SetIsDead();
	bool GetIsDead();
	sf::Sprite& GetSprite1() { return m_sprite1; };
	sf::Sprite& GetSprite2() { return m_sprite2; };
	b2Body* GetBody() { return m_body; };

#pragma endregion
#pragma region METHODS

	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

#pragma endregion

protected:

#pragma region SFML

	//SPRITE & TEXTURE
	sf::Sprite m_sprite1;
	std::string m_spriteAdress1;
	sf::Texture m_texture1;
	sf::Sprite m_sprite2;
	std::string m_spriteAdress2;
	sf::Texture m_texture2;

#pragma endregion
#pragma region BOX2D

	//B2D
	b2Body* m_body = nullptr;
	//USERDATA
	UserData* m_userData = new UserData(UserDataType::TRAIL);
	static long m_localTrailId;
	static long GetGlobalId();

#pragma endregion

	bool m_isDead = false;

};