#include "background.h"

Background::Background(Game& game, std::string spriteAdress) : m_game(game), m_spriteAdress(spriteAdress)
{
	Init();
}

void Background::Init() 
{
	//star
	m_texture.loadFromFile(m_spriteAdress);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().y * 0.5f, m_texture.getSize().x * 0.5f));
	m_sprite.setPosition();
	
}
void Background::Update() 
{
	m_sprite.setPosition(sf::Vector2f(0.0f, m_sprite.getPosition().y-1));
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}