#pragma once

#include "Rect.h"
#include "Platform.h"

#include <SFML/Graphics.hpp>

enum class ObjectState : int
{
   Standing,
   Sliding,
   Flying,
   Bouncing,
   Sledding
};

enum class WindDirection : bool
{
   West,
   East
};

class Object : public sf::Drawable
{
public:
   Object(const jp::math::Rect<float>& rect, const jp::math::Vector2<float>& velocity, const jp::math::Vector2<float>& acceleration);

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

   void update(float seconds, const std::vector<jp::physics::PlatformSegment>& segments);

   void log();

   //ObjectState checkCollision(jp::math::Rect<float>& newRect, float seconds, const std::vector<jp::physics::Platform>& platforms);


   jp::math::Rect<float> getRect() const;

   struct Attributes
   {
      jp::math::Rect<float> rect;
      jp::math::Vector2<float> velocity;
      jp::math::Vector2<float> acceleration;
      ObjectState state = ObjectState::Standing;
   } mAttributes;

   bool checkVerticalCollision(const jp::math::Segment<float>& objectSegment,
      const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const;

   bool checkHorizontalCollision(const jp::math::Segment<float>& objectSegment,
      const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const;

   bool checkDiagonalCollision(const jp::math::Segment<float>& objectSegment,
      const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const;

   bool logging = false;

   float GRAVITY = 1000.f;
   float WIND = 0.f;
   float BOUNCE_FACTOR = 0.5f;
   float OFFSET = 0.5f;
   WindDirection windDirection = WindDirection::East;
};