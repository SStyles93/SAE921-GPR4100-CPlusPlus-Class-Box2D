#include "game.h"
#include "star.h"

#pragma region CONSTRUCTOR

Star::Star(Game& game, sf::Vector2f pos, sf::Vector2f scale, float angle) : m_game(game)
{
	TextureManager* texture_manager = TextureManager::Instance();
	m_sprite.setTexture(texture_manager->GetStarTexture());
	m_sprite.setOrigin(texture_manager->GetStarTexture().getSize().x * 0.5f, texture_manager->GetStarTexture().getSize().y * 0.5f);
	m_sprite.setPosition(pos);
	m_sprite.setScale(scale);
	m_sprite.setRotation(angle);
}

#pragma endregion
#pragma region GAME METHODS

void Star::Update()
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 5.0f));
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}

#pragma endregion