#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/b2_math.h>

//#include <cmath>
//#define _MATH_DEFINES_DEFINED
//#define _USE_MATH_DEFINES // for C++

//#define M_PI 3.14159265358979323846

//#define _USE_MATH_DEFINES
//#include <cmath> 

#include <corecrt_math_defines.h>

#pragma region MATHS

float dotProduct(sf::Vector2f vec1_, sf::Vector2f vec2_);
float determinant(sf::Vector2f vec1_, sf::Vector2f vec2_);
float vecLength(sf::Vector2f vec_);
float vecDistance(sf::Vector2f p1, sf::Vector2f p2);
float vecAngle(sf::Vector2f vec1_, sf::Vector2f vec2_);
float degToRad(float degrees_);
float radToDeg(float radians_);

#pragma endregion
#pragma region CONVERSION

b2Vec2 pixelsToMeters(sf::Vector2f pixels);
b2Vec2 pixelsToMeters(sf::Vector2u pixels);
float pixelsToMeters(float pixels);
sf::Vector2f metersToPixels(b2Vec2 meters);

#pragma endregion

static constexpr float pixelsMetersRatio = 100.0f;
constexpr float epsilon = 0.0001f;



