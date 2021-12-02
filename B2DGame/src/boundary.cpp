#include <iostream>

#include "boundary.h"
#include "game.h"
#include "SFML_Utilities.h"

Boundary::Boundary(Game& game_, sf::Vector2f pos_, sf::Vector2f size_) : m_game(game_)
{
    Init(pos_, size_);
}

void Boundary::Init(sf::Vector2f pos_, sf::Vector2f size_) {

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2BodyType::b2_staticBody; // Static !!! it does not move when something collides
    bodyDef.position.Set(pixelsToMeters(pos_).x, pixelsToMeters(pos_).y);
    bodyDef.angle = 0.0f;
    m_body = this->m_game.getWorld().CreateBody(&bodyDef);

    // Shape of the physical (A box)
    b2PolygonShape boundaryBox;
    boundaryBox.SetAsBox(
        pixelsToMeters(size_.x),
        pixelsToMeters(size_.y),
        b2Vec2_zero,
        degToRad(.0f));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &boundaryBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.2f;
    playerFixtureDef.restitution = 0.01f; // Make it bounce a little bit
    m_body->CreateFixture(&playerFixtureDef);

    // Defining the shape
    m_shape.setSize(size_);
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOrigin(0.5f * size_.x, 0.5f * size_.y);

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

