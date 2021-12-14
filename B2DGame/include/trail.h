#pragma once

#include "UserData.h"
#include "object.h"
#include "SFML_Utilities.h"

class Game;

class Trail : public sf::Drawable, public sf::Transformable
{
protected:

#pragma region SFML

	//SPRITE & TEXTURE
	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

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

public:

#pragma region GETTER/SETTER

	long GetLocalId();
	void SetIsDead();
	bool GetIsDead();
	sf::Sprite& GetSprite() { return m_sprite; };
	b2Body* GetBody() { return m_body; };

#pragma endregion
#pragma region CONSTRUCTOR

	explicit Trail(b2World& world, sf::Vector2f pos);

#pragma endregion
#pragma region METHODS

	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

#pragma endregion

};