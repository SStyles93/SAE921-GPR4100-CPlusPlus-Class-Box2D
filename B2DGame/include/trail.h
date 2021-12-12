#pragma once

#include "UserData.h"
#include "object.h"
#include "SFML_Utilities.h"

class Game;

class Trail : public sf::Drawable, public sf::Transformable
{
protected:
	//Root
	//Game& m_game;

	//Star
	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

	sf::RectangleShape m_shape;

	//B2D
	b2Body* m_body = nullptr;

	UserData* m_userData = new UserData(UserDataType::TRAIL);
	static long m_localTrailId;
	static long getGlobalId();

	bool m_isDead = false;

public:

	long getLocalId();
	void setIsDead();
	bool getIsDead();

	sf::Sprite& GetSprite() { return m_sprite; };

	explicit Trail(b2World& world, sf::Vector2f pos);
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};