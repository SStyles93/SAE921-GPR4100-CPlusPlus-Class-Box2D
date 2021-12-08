#include "TextureManager.h"

TextureManager* TextureManager::m_textureManager = nullptr;

TextureManager::TextureManager()
{
    m_starTexture.loadFromFile("data/sprites/star.png");
    m_trailTexture.loadFromFile("data/sprites/trail.png");
}


/**
 * Static methods should be defined outside the class.
 */
TextureManager* TextureManager::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (m_textureManager == nullptr) {
        m_textureManager = new TextureManager();
    }
    return m_textureManager;
}

sf::Texture& TextureManager::GetStarTexture() 
{
    return m_starTexture;
}
sf::Texture& TextureManager::GetTrailTexture() 
{
    return m_trailTexture;
}