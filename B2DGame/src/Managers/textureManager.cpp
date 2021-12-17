#include "Managers/textureManager.h"

TextureManager* TextureManager::m_textureManager = nullptr;

TextureManager::TextureManager()
{
    m_starTexture.loadFromFile("data/sprites/star.png");
    m_trailTexture1.loadFromFile("data/sprites/meteor.png");
    m_trailTexture2.loadFromFile("data/sprites/meteorTrail.png");
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
#pragma region GETTER/SETTER

sf::Texture& TextureManager::GetStarTexture() 
{
    return m_starTexture;
}
sf::Texture& TextureManager::GetTrailTexture1() 
{
    return m_trailTexture1;
}
sf::Texture& TextureManager::GetTrailTexture2()
{
    return m_trailTexture2;
}
#pragma endregion