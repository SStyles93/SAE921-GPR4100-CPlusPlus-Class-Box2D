#include "game.h"
#include "object.h"
#include "SFML_Utilities.h"

Object::Object(Game& game, sf::Vector2f pos, sf::Vector2f size, std::string spriteAdress) : m_game(game), m_spriteAdress(spriteAdress)
{
	Init(pos, size);
}

void Object::Init(sf::Vector2f pos, sf::Vector2f size)
{
	m_texture.loadFromFile(m_spriteAdress);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().y * 0.5f, m_texture.getSize().x * 0.5f));
	m_sprite.setPosition(sf::Vector2f(pos));

	////B2D
	//b2BodyDef bodyDef;
	//bodyDef.fixedRotation = true;
	//bodyDef.type = b2BodyType::b2_staticBody;
	//bodyDef.position.Set(pixelsToMeters(pos).x, pixelsToMeters(pos).y);
	//bodyDef.angle = 0.0f;
	//m_body = this->m_game.getWorld().CreateBody(&bodyDef);

	////Phisics
	//b2PolygonShape boundaryBox;
	//boundaryBox.SetAsBox(
	//	pixelsToMeters(size.x),
	//	pixelsToMeters(size.y),
	//	b2Vec2_zero,
	//	degToRad(.0f));
	////Fixture
	//b2FixtureDef playerFixtureDef;
	//playerFixtureDef.shape = &boundaryBox;
	//playerFixtureDef.density = 1.0f;
	//playerFixtureDef.friction = 0.2f;
	//playerFixtureDef.restitution = 0.00f; // Make it bounce a little bit
	//m_body->CreateFixture(&playerFixtureDef);

	////DefShap
	//m_shape.setSize(size);
	//m_shape.setFillColor(sf::Color(255,255,255,200));
	//m_shape.setOrigin(0.5f * size.x, 0.5f * size.y);


	
}
void Object::Update() 
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y+.1f));
	/*const auto& b2Position = m_body->GetPosition();
	m_shape.setPosition(metersToPixels(b2Position));
	const auto b2rotation = m_body->GetAngle();
	m_shape.setRotation(-1.0f * radToDeg(b2rotation));*/
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}