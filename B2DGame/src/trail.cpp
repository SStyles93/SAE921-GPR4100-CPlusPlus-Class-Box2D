#include "game.h"
#include "trail.h"

#include "iostream"

long Trail::m_localTrailId = 0;

#pragma region CONSTRUCTOR

Trail::Trail(b2World& world, sf::Vector2f pos , float scale)
{
    //SET TEXTURE
	TextureManager* textureManager = TextureManager::Instance();
	m_sprite1.setScale(sf::Vector2f(scale, scale));
	m_sprite1.setTexture(textureManager->GetTrailTexture1());
	m_sprite1.setOrigin(textureManager->GetTrailTexture1().getSize().x * 0.5f, textureManager->GetTrailTexture1().getSize().y * 0.5f);
    m_sprite1.setPosition(0.0f * scale, 0.0f * scale);
    m_sprite2.setScale(sf::Vector2f(scale, scale));
    m_sprite2.setTexture(textureManager->GetTrailTexture2());
    m_sprite2.setOrigin(textureManager->GetTrailTexture2().getSize().x * 0.5f, textureManager->GetTrailTexture2().getSize().y * 0.5f);
    m_sprite2.setPosition(-1.66f * scale, -33.33f * scale);
    m_sprite3.setScale(sf::Vector2f(scale, scale));
    m_sprite3.setTexture(textureManager->GetTrailTexture2());
    m_sprite3.setOrigin(textureManager->GetTrailTexture2().getSize().x * 0.5f, textureManager->GetTrailTexture2().getSize().y * 0.5f);
    m_sprite3.setPosition(-1.66f * scale, -50.0f * scale);
    m_sprite3.setColor(sf::Color(255, 255, 255, 100));

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
    /*hitBox.SetAsBox(
        pixelsToMeters(textureManager->GetTrailTexture1().getSize().x),
        pixelsToMeters(textureManager->GetTrailTexture1().getSize().y * 0.5f));*/
    hitBox.SetAsBox(
        textureManager->GetTrailTexture1().getSize().x * 0.5f * (scale / 3) / Game::pixelsMetersRatio,
        textureManager->GetTrailTexture1().getSize().y * 0.5f * (scale / 3) / Game::pixelsMetersRatio);

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
        m_sprite3.setColor(sf::Color(255, 255, 255, (255 * 0.5f * sinf(graphicPosition.y))));
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
        target.draw(m_sprite2, states);
        target.draw(m_sprite1, states);
        target.draw(m_sprite3, states);
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