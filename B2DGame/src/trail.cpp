#include "game.h"
#include "trail.h"

Trail::Trail(Game& game, sf::Vector2f pos, float angle) : m_game(game)
{
	TextureManager* texture_manager = TextureManager::Instance();
	m_sprite.setTexture(texture_manager->GetTrailTexture());
	m_sprite.setOrigin(texture_manager->GetTrailTexture().getSize().x * 0.5f, texture_manager->GetTrailTexture().getSize().y * 0.5f);
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle);
}

void Trail::Update()
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 10.0f));
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}