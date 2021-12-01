#include "character.h"
#include "game.h"

Character::Character(Game& game, sf::RenderWindow& window) : m_game(game), m_window(window)
{

}
void Character::Init() 
{
	//Define Shape
	m_shape.setOrigin(0.0f, 0.0f);
	m_shape.setPosition(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);

	//Define Box2D elements
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	
	b2Vec2 windowSize = Game::pixelsToMeters(m_window.getSize());
	bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);
	m_body = this->m_game.getWorld().CreateBody(&bodyDef);
	
	//Shape of phisical elements
	b2CircleShape characterShape;

	//The Fixture (phisic react)
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &characterShape;
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
	m_shape.setPosition(graphicPosition);
}
void Character::Render() 
{
	m_window.draw(m_shape);
}
void Character::SetPixelsPosition(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity)
{

}