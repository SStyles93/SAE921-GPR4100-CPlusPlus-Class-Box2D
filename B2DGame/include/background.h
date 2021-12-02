#pragma once

#include "SFML/Graphics.hpp"

class Game;

class Background : public sf::Drawable, public sf::Transformable
{
private:
	//Root
	Game& m_game;

	//Star
	sf::Sprite m_sprite;
	std::string m_spriteAdress;
	sf::Texture m_texture;

public:

	explicit Background(Game& game, std::string m_spriteAdress);

	void Init();
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
 
