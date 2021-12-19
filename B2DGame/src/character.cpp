#include "Managers/sfmlUtilities.h"

#include "character.h"
#include "game.h"

#include "iostream"

#pragma region CONSTRUCTOR

Character::Character(Game& game) : m_game(game)
{
	m_mainSpriteAdress = "data/sprites/capsule1.png";
	m_secondSpriteAdress = "data/sprites/capsuleSpeed1.png"; 
	m_thirdSpriteAdress = "data/sprites/capsuleTrail.png";
}

#pragma endregion
#pragma region GAME METHODS

void Character::Init(sf::Vector2u winsize)
{
#pragma region SFML

	//Define SFML elements
	m_mainTexture.loadFromFile(m_mainSpriteAdress);
	m_mainSprite.setTexture(m_mainTexture);
	m_mainSprite.setOrigin(sf::Vector2f(m_mainTexture.getSize().x * 0.5f, m_mainTexture.getSize().y * 0.5f));

	m_secondTexture.loadFromFile(m_secondSpriteAdress);
	m_secondSprite.setTexture(m_secondTexture);
	m_secondSprite.setOrigin(sf::Vector2f(m_mainTexture.getSize().y * 0.5f, m_mainTexture.getSize().x * 0.5f));
	m_secondSprite.setPosition(0, 0);
	SetSpriteAlpha(m_secondSprite, 0);

	m_thirdTexture.loadFromFile(m_thirdSpriteAdress);
	m_thirdSprite.setTexture(m_thirdTexture);
	m_thirdSprite.setOrigin(sf::Vector2f(m_mainTexture.getSize().y * 0.5f, m_mainTexture.getSize().x * 0.5f));
	m_thirdSprite.setPosition(0, 125);
	SetSpriteAlpha(m_thirdSprite, 0);

#pragma endregion
#pragma region BOX2D

	//Define Box2D elements
	b2BodyDef bodyDef;
	
	b2Vec2 windowSize = pixelsToMeters(winsize);

	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(windowSize.x * 0.5f, windowSize.y * 0.5f);
	bodyDef.angularDamping = 0.75f;
	bodyDef.linearDamping = 0.75f;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
	m_body = this->m_game.GetWorld().CreateBody(&bodyDef);
	
	//Shape of phisical elements
	/*b2PolygonShape hitBox;
	hitBox.SetAsBox(pixelsToMeters(m_mainTexture.getSize().x * 0.5f), pixelsToMeters(m_mainTexture.getSize().y * 0.5f));*/
	b2CircleShape hitBox;
	hitBox.m_radius = m_mainTexture.getSize().x * 0.5f / m_game.pixelsMetersRatio;

	//The Fixture (phisic react)
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &hitBox;
	playerFixtureDef.density = 1.0f;
	playerFixtureDef.friction = 0.0f;
	m_body->CreateFixture(&playerFixtureDef);

#pragma endregion
}
void Character::Update()
{
	// Get the position of the body
	b2Vec2 bodyPos = m_body->GetPosition();
	// Translate meters to pixels
	sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);
	// Set the position of the Graphic object
	setPosition(graphicPosition);
}
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_mainSprite, states);
	target.draw(m_secondSprite, states);
	target.draw(m_thirdSprite, states);
}

#pragma endregion
#pragma region OBJECT METHODS

#pragma region Physical

//Applies a given force to the m_body
void Character::Move(b2Vec2 b2Vec)
{
	b2Vec2 force(b2Vec);
	b2Vec2 localForce = m_body->GetLocalVector(force);

	if (b2Abs(m_body->GetLinearVelocity().Length()) < 5.0f) {
		m_body->ApplyForceToCenter(localForce, true);

		if (b2Abs(m_body->GetLinearVelocity().Length()) < epsilon) {
			m_body->SetLinearVelocity(b2Vec2_zero);
		}
	}
}

#pragma endregion
#pragma region Graphical

//Sets the Alpha Value of a references sprite
void Character::SetSpriteAlpha(sf::Sprite& sprite, float alphaValue) 
{
	sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, alphaValue));
}
//Maximizes the AlphaValue of the Thruster
void Character::MaxThrusterAlphaValue()
{
	SetSpriteAlpha(m_secondSprite, m_secondSpriteAlphaValue = 255.0f);
	SetSpriteAlpha(m_thirdSprite, m_thirdSpriteAlphaValue = 255.0f);
}
//Lowers the AlphaValue of the Thruster
void Character::LowerThrusterAlphaValue() 
{
	if (m_secondSpriteAlphaValue >= 0.0f)
	{
		SetSpriteAlpha(m_secondSprite, m_secondSpriteAlphaValue -= m_secondSpriteAlphaValue / 20);
	}
	if (m_thirdSpriteAlphaValue >= 0.0f)
	{
		SetSpriteAlpha(m_thirdSprite, m_thirdSpriteAlphaValue -= m_thirdSpriteAlphaValue / 10);
	}
}
//Resets the Color to maxValue
void Character::ResetColor() 
{
	m_mainSprite.setColor(sf::Color(255, 255, 255, 255));
}

#pragma endregion
#pragma region Stats

//Returns the characters health
float Character::GetHealth()
{
	return m_health;
}
//Lowers the characters health
void Character::SetDamage(float damage)
{
	m_health -= damage;
	m_mainSprite.setColor(sf::Color::Red);
	
}

#pragma endregion

#pragma endregion