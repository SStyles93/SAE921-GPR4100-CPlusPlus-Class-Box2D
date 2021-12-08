#pragma once

#include "SFML/Graphics.hpp"

class TextureManager
{
protected:
	TextureManager();

	static TextureManager* m_textureManager;

	sf::Texture m_starTexture;

public:

	//deletes the copies of the texture manager
	TextureManager(TextureManager& other) = delete;
	//prevents
	void operator=(const TextureManager&) = delete;

	/*This is the static method that controls the access to the singleton
		* instance.On the first run, it creates a singleton objectand places it
		* into the static field.On subsequent runs, it returns the client existing
		* object stored in the static field.
		* 
		*/

	static TextureManager* Instance();

	//GETTERS
	sf::Texture& GetStarTexture();

};