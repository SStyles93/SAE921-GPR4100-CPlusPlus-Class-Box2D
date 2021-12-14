#include "game.h"
#include "trail.h"

#include "iostream"

long Trail::m_localTrailId = 0;

#pragma region CONSTRUCTOR

Trail::Trail(b2World& world, sf::Vector2f pos)
{
    //SET TEXTURE
	TextureManager* textureManager = TextureManager::Instance();
	m_sprite.setScale(sf::Vector2f(3, 3));
	m_sprite.setTexture(textureManager->GetTrailTexture());
	m_sprite.setOrigin(textureManager->GetTrailTexture().getSize().x * 0.5f, textureManager->GetTrailTexture().getSize().y * 0.5f);
    m_sprite.setPosition(0, -75);

    //BODYDEF
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.angularDamping = 0.01f;
    bodyDef.linearDamping = 0.01f;

    // SET DATAS
    m_userData->setLocalId(GetGlobalId());
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    //CreateBody
    m_body = world.CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2PolygonShape hitBox;
    hitBox.SetAsBox(
        pixelsToMeters(textureManager->GetTrailTexture().getSize().x),
        pixelsToMeters(textureManager->GetTrailTexture().getSize().y * 0.5f));
    /*hitBox.SetAsBox(0.2f, 0.5f);*/

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.0f;

    m_body->CreateFixture(&playerFixtureDef);
    b2Vec2 physicalPos = pixelsToMeters(pos);
    m_body->SetTransform(physicalPos, 0.0f);
    //m_body->SetTransform(b2Vec2(0, 0), 0);
}

#pragma endregion
#pragma region METHODS

void Trail::Update()
{   
    if (!m_isDead) 
    {
        // Get the position of the body
        b2Vec2 bodyPos = m_body->GetPosition();
        // Translate meters to pixels
        sf::Vector2f graphicPosition = metersToPixels(bodyPos);
        // Set the position of the Graphic object
        setPosition(graphicPosition);
    }
    if (m_isDead)
    {
            m_body->DestroyFixture(m_body->GetFixtureList());
    }
}
void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_isDead) 
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }
}

#pragma endregion
#pragma region GETTER/SETTER

long Trail::GetLocalId()
{
	return m_userData->getLocalId();
}
long Trail::GetGlobalId()
{
	return m_localTrailId++;
}
void Trail::SetIsDead()
{
    m_isDead = true;
}
bool Trail::GetIsDead()
{
    return m_isDead;
}

#pragma endregion