#include "SFML_Utilities.h"

#include "character.h"
#include "game.h"

#include "iostream"

#pragma region CONSTRUCTOR

Character::Character(Game& game) : m_game(game)
{
	m_mainSpriteAdress = "data/sprites/rocket.png";
	m_secondSpriteAdress = "data/sprites/fire.png";
}

#pragma endregion
#pragma region GAME METHODS

void Character::Init(sf::Vector2u winsize)
{
	//Define SFML elements
	m_mainTexture.loadFromFile(m_mainSpriteAdress);
	
	m_mainSprite.setTexture(m_mainTexture);
	m_mainSprite.setOrigin(sf::Vector2f(m_mainTexture.getSize().x * 0.5f, m_mainTexture.getSize().y * 0.5f));

	
	////change of color for damage
	//m_mainSprite.setColor(sf::Color::Red);

	m_secondTexture.loadFromFile(m_secondSpriteAdress);
	m_secondSprite.setTexture(m_secondTexture);
	m_secondSprite.setOrigin(sf::Vector2f(m_mainTexture.getSize().y * 0.5f, m_mainTexture.getSize().x * 0.5f));
	m_secondSprite.setPosition(15, 125);
	SetSpriteAlpha(m_secondSprite, 0);
	

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
	b2PolygonShape hitBox;
	hitBox.SetAsBox(pixelsToMeters(m_mainTexture.getSize().x * 0.5f), pixelsToMeters(m_mainTexture.getSize().y * 0.5f));
	/*b2CircleShape hitBox;
	hitBox.m_radius = pixelsToMeters(m_mainSprite.getTexture()->getSize().x);*/

	//The Fixture (phisic react)
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &hitBox;
	playerFixtureDef.density = 1.0f;
	playerFixtureDef.friction = 0.0f;
	m_body->CreateFixture(&playerFixtureDef);
}
void Character::Update()
{
	// Get the position of the body
	b2Vec2 bodyPos = m_body->GetPosition();
	// Translate meters to pixels
	sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);
	// Set the position of the Graphic object
	setPosition(graphicPosition);
	/*float angle = m_body->GetAngle();
	setRotation(radToDeg(angle));*/

	/*std::cout << "CHARACTER POS\n" << "----------------\n";
	std::cout << m_body->GetPosition().x << "\n";
	std::cout << graphicPosition.x << "\n";
	std::cout << m_body->GetPosition().y << "\n";
	std::cout << graphicPosition.y << "\n";*/
}
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_mainSprite, states);
	target.draw(m_secondSprite, states);
}

#pragma endregion
#pragma region OBJECT METHODS

void Character::Thruster(b2Vec2 b2Vec) 
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
void Character::MoveRight(b2Vec2 force)
{
	//m_body->SetTransform(b2Vec2(m_body->GetPosition() + b2Vec2(0.25, 0.0)), m_body->GetAngle());
	m_body->ApplyForceToCenter(force, true);
}
void Character::MoveLeft(b2Vec2 force)
{
	//m_body->SetTransform(b2Vec2(m_body->GetPosition() + b2Vec2(-0.25,0.0)), m_body->GetAngle());
	m_body->ApplyForceToCenter(force, true);
}
void Character::SetSpriteAlpha(sf::Sprite& sprite, float alphaValue) 
{
	sprite.setColor(sf::Color(m_secondSprite.getColor().r, m_secondSprite.getColor().g, m_secondSprite.getColor().b, alphaValue));
}
float Character::GetHealth() 
{
	return m_health;
}
void Character::SetDamage(float damage)
{
	m_health -= damage;
}

#pragma endregion