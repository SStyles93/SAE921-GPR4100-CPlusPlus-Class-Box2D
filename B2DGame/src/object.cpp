#include "game.h"
#include "object.h"
#include "SFML_Utilities.h"

Object::Object(Game& game, sf::Vector2f pos, float angle) : m_game(game)
{
	TextureManager* texture_manager = TextureManager::Instance();
	m_sprite.setTexture(texture_manager->GetStarTexture());
	m_sprite.setOrigin(texture_manager->GetStarTexture().getSize().x * 0.5f, texture_manager->GetStarTexture().getSize().y * 0.5f);
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle);

}

void Object::Update() 
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y+1.0f));
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}