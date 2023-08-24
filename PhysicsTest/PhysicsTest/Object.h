#pragma once

#include "Rect.h"
#include "Platform.h"

#include <SFML/Graphics.hpp>

enum class ObjectState
{
   Standing,
   Sliding,
   Flying,
   Bouncing,
   Sledding
};

class Object : public sf::Drawable
{
public:
   Object(const jp::math::Rect<float>& rect, const jp::math::Vector2<float>& velocity, const jp::math::Vector2<float>& acceleration);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   void update(float seconds, const std::vector<jp::physics::Platform>& platforms);

   void log();

   //ObjectState checkCollision(jp::math::Rect<float>& newRect, float seconds, const std::vector<jp::physics::Platform>& platforms);

   jp::math::Rect<float> getRect() const;

   jp::math::Rect<float> mRect;
   jp::math::Vector2<float> mVelocity;
   jp::math::Vector2<float> mAcceleration;
   ObjectState mState = ObjectState::Standing;

   float GRAVITY = 1000.f;
   float WIND = 0.f;
   float BOUNCE_FACTOR = 0.5f;
};