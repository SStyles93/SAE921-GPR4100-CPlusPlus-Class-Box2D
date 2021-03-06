#pragma once

#include "SFML/Graphics.hpp"

class TextureManager
{
protected:
#pragma region CONSTRUCTOR (SINGLETON)

	TextureManager();
	static TextureManager* m_textureManager;

#pragma endregion
#pragma region TEXTURES

	sf::Texture m_starTexture;
	sf::Texture m_trailTexture;

#pragma endregion

public:
#pragma region DELETERS

	//deletes the copies of the texture manager
	TextureManager(TextureManager& other) = delete;
	//prevents
	void operator=(const TextureManager&) = delete;

#pragma endregion

/*This is the static method that controls the access to the singleton
		* instance.On the first run, it creates a singleton objectand places it
		* into the static field.On subsequent runs, it returns the client existing
		* object stored in the static field.
		* 
		*/
#pragma region INSTANCE (SINGLETON)

	static TextureManager* Instance();

#pragma endregion
#pragma region GETTER/SETTER

	sf::Texture& GetStarTexture();
	sf::Texture& GetTrailTexture();

#pragma endregion

};