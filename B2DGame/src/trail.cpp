#include "game.h"
#include "trail.h"

long Trail::m_localTrailId = 0;

Trail::Trail(b2World& world, sf::Vector2f pos, float angle)
{
    //SET TEXTURE
	TextureManager* textureManager = TextureManager::Instance();
	m_sprite.setTexture(textureManager->GetTrailTexture());
	m_sprite.setOrigin(textureManager->GetTrailTexture().getSize().x * 0.5f, textureManager->GetTrailTexture().getSize().y * 0.5f);
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle);

    //BODYDF
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;

    // SET DATAS
    m_userData->setLocalId(getGlobalId());
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    m_body = world.CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2CircleShape hitBox;
    hitBox.m_radius = pixelsToMeters(textureManager->GetTrailTexture().getSize().x * 0.5f);

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.0f;

    m_body->CreateFixture(&playerFixtureDef);
}

void Trail::Update()
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 10.0f));
    
    // Get the position of the body
    b2Vec2 bodyPos = m_body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}

long Trail::getLocalId()
{
	return m_userData->getLocalId();
}
long Trail::getGlobalId()
{
	return m_localTrailId++;
}
void Trail::setIsDead()
{
    m_isDead = true;
}
bool Trail::getIsDead()
{
    return m_isDead;
}