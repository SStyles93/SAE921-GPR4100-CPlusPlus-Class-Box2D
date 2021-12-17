#include "boundary.h"
#include "game.h"
#include "Managers/sfmlUtilities.h"

Boundary::Boundary(Game& game, sf::Vector2f pos, sf::Vector2f size, bool flag) : m_game(game)
{
    if (flag) m_userData = new UserData(UserDataType::LIMIT);
    Init(pos, size);
}

void Boundary::Init(sf::Vector2f pos, sf::Vector2f size) {

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    bodyDef.position.Set(pixelsToMeters(pos).x, pixelsToMeters(pos).y);
    bodyDef.angle = 0.0f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
    m_body = this->m_game.GetWorld().CreateBody(&bodyDef);

    // Shape of the physical (box)
    b2PolygonShape boundaryBox;
    boundaryBox.SetAsBox(
        pixelsToMeters(size.x),
        pixelsToMeters(size.y),
        b2Vec2_zero,
        degToRad(.0f));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &boundaryBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.00f; // Make it bounce a little bit
    m_body->CreateFixture(&playerFixtureDef);
    
    // Defining the shape
    m_shape.setSize(size);
    //m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOrigin(0.5f * size.x, 0.5f * size.y);
}

void Boundary::Update() {

    const auto& b2Position = m_body->GetPosition();
    m_shape.setPosition(metersToPixels(b2Position));
    const auto b2rotation = m_body->GetAngle();
    m_shape.setRotation(-1.0f * radToDeg(b2rotation));

}

void Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_shape, states);
}

