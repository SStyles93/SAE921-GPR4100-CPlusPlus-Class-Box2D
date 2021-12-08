#include "game.h"
#include "star.h"

Star::Star(Game& game, sf::Vector2f pos, float angle) : m_game(game)
{
	TextureManager* texture_manager = TextureManager::Instance();
	m_sprite.setTexture(texture_manager->GetStarTexture());
	m_sprite.setOrigin(texture_manager->GetStarTexture().getSize().x * 0.5f, texture_manager->GetStarTexture().getSize().y * 0.5f);
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle);
}

void Star::Update()
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 5.0f));
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}