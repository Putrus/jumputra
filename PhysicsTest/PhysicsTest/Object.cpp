#include "Functions.h"
#include "Segment.h"
#include "Object.h"

#include <algorithm>
#include <iostream>

Object::Object(const jp::math::Rect<float>& rect, const jp::math::Vector2<float>& velocity, const jp::math::Vector2<float>& acceleration)
   : mAttributes({ rect, velocity, acceleration })
{}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   sf::Color color = sf::Color::Red;
   sf::VertexArray rectangle(sf::Quads, 4);
   rectangle[0] = sf::Vertex({ mAttributes.rect.left, mAttributes.rect.top }, color);
   rectangle[1] = sf::Vertex({ mAttributes.rect.getRight(), mAttributes.rect.top}, color);
   rectangle[2] = sf::Vertex({ mAttributes.rect.getRight(), mAttributes.rect.getBottom()}, color);
   rectangle[3] = sf::Vertex({ mAttributes.rect.left, mAttributes.rect.getBottom() }, color);
   target.draw(rectangle, states);
}

void Object::update(float seconds, const std::vector<jp::physics::PlatformSegment>& segments)
{
  /* if (windDirection == WindDirection::East)
   {
      WIND += 50.f * seconds;
      if (WIND > 100.f)
      {
         windDirection = WindDirection::West;
      }
   }
   else
   {
      WIND += -50.f * seconds;
      if (WIND < -100.f)
      {
         windDirection = WindDirection::East;
      }
   }*/
   //potential new velocity and rect of the object
   jp::math::Vector2<float> newVelocity = mAttributes.velocity +
      (mAttributes.acceleration + jp::math::Vector2<float>(WIND, GRAVITY)) * seconds;
   jp::math::Rect<float> newRect = getRect() + (mAttributes.velocity + newVelocity) * seconds / 2.f;

   Attributes newAttributes = { newRect, newVelocity, mAttributes.acceleration, ObjectState::Flying };

   for (const auto& platformSegment : segments)
   {
      //vertical segment
      if (platformSegment.segment.isVertical())
      {
         checkVerticalCollision({ newRect.getLeftTop(),
            newRect.getRightTop() }, platformSegment, newAttributes);
         checkVerticalCollision({ newRect.getLeftBottom(),
            newRect.getRightBottom() }, platformSegment, newAttributes);
      }
      else if (platformSegment.segment.isHorizontal())
      {
         checkHorizontalCollision({ newRect.getLeftTop(),
            newRect.getLeftBottom() }, platformSegment, newAttributes);
         checkHorizontalCollision({ newRect.getRightTop(),
            newRect.getRightBottom() }, platformSegment, newAttributes);
      }
      else if (platformSegment.segment.isDiagonal())
      {
         checkDiagonalCollision({ newRect.getLeftTop(),
            newRect.getRightTop() }, platformSegment, newAttributes);
         checkDiagonalCollision({ newRect.getLeftBottom(),
            newRect.getRightBottom() }, platformSegment, newAttributes);
      }
      else
      {
         //...error
      }
   }
   mAttributes = std::move(newAttributes);
}

jp::math::Rect<float> Object::getRect() const
{
   return mAttributes.rect;
}

void Object::log()
{
   std::cout << "Pos = " << mAttributes.rect.getPosition() << std::endl;
   std::cout << "A = " << mAttributes.acceleration << std::endl;
   std::cout << "V = " << mAttributes.velocity << std::endl;
   std::cout << "State = " << (int)mAttributes.state << std::endl;
}

bool Object::checkVerticalCollision(const jp::math::Segment<float>& objectSegment,
   const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const
{
   const jp::math::Vector2<float>& a = objectSegment.a.x < objectSegment.b.x ? objectSegment.a : objectSegment.b;
   const jp::math::Vector2<float>& b = objectSegment.a.x < objectSegment.b.x ? objectSegment.b : objectSegment.a;
   const jp::math::Vector2<float>& c = platformSegment.segment.a.y < platformSegment.segment.b.y ? platformSegment.segment.a : platformSegment.segment.b;
   const jp::math::Vector2<float>& d = platformSegment.segment.a.y < platformSegment.segment.b.y ? platformSegment.segment.b : platformSegment.segment.a;
   if (a.y > c.y && a.y < d.y && c.x > a.x && c.x < b.x)
   {
      if (mAttributes.rect.top >= d.y)
      {
         newAttributes.rect.top = d.y;
         //bounce or stay depends on gravity sign
         if (GRAVITY < 0.f)
         {
            if ((platformSegment.type == jp::physics::PlatformType::Ordinary ||
               platformSegment.type == jp::physics::PlatformType::Sticky))
            {
               newAttributes.state = ObjectState::Standing;
               if (mAttributes.state == ObjectState::Flying)
               {
                  newAttributes.velocity.x = 0.f;
               }
            }
            else if (platformSegment.type == jp::physics::PlatformType::Slippery)
            {
               newAttributes.state = ObjectState::Sliding;
            }
         }
         else
         {
            newAttributes.state = ObjectState::Flying;
         }
      }
      else if (mAttributes.rect.getBottom() <= c.y)
      {
         newAttributes.rect.top = c.y - newAttributes.rect.height;
         //bounce or stay depends on gravity sign
         if (GRAVITY > 0.f)
         {
            if ((platformSegment.type == jp::physics::PlatformType::Ordinary ||
               platformSegment.type == jp::physics::PlatformType::Sticky))
            {
               newAttributes.state = ObjectState::Standing;
               if (mAttributes.state == ObjectState::Flying)
               {
                  newAttributes.velocity.x = 0.f;
               }
            }
            else if (platformSegment.type == jp::physics::PlatformType::Slippery)
            {
               newAttributes.state = ObjectState::Sliding;
            }
         }
         else
         {
            newAttributes.state = ObjectState::Flying;
         }
      }
      else
      {
         if (mAttributes.rect.getCenter().x > d.x)
         {
            newAttributes.rect.left = d.x;
            if (mAttributes.state == ObjectState::Flying ||
               mAttributes.state == ObjectState::Sliding)
            {
               newAttributes.velocity.x = mAttributes.velocity.x * -1.f;
            }
         }
         else
         {
            newAttributes.rect.left = c.x - newAttributes.rect.width;
            if (mAttributes.state == ObjectState::Flying ||
               mAttributes.state == ObjectState::Sliding)
            {
               newAttributes.velocity.x = mAttributes.velocity.x * -1.f;
            }
         }
      }
      //return the distance between intersecting segments
      newAttributes.velocity.y = 0.f;
      return true;
   }
   return false;
}

bool Object::checkHorizontalCollision(const jp::math::Segment<float>& objectSegment,
   const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const
{
   const jp::math::Vector2<float>& a = objectSegment.a.y < objectSegment.b.y ? objectSegment.a : objectSegment.b;
   const jp::math::Vector2<float>& b = objectSegment.a.y < objectSegment.b.y ? objectSegment.b : objectSegment.a;
   const jp::math::Vector2<float>& c = platformSegment.segment.a.x < platformSegment.segment.b.x ? platformSegment.segment.a : platformSegment.segment.b;
   const jp::math::Vector2<float>& d = platformSegment.segment.a.x < platformSegment.segment.b.x ? platformSegment.segment.b : platformSegment.segment.a;
   if (a.x > c.x && a.x < d.x && c.y > a.y && c.y < b.y)
   {
      if (mAttributes.rect.left >= d.x)
      {
         newAttributes.rect.left = d.x;
         if (mAttributes.state == ObjectState::Flying ||
            mAttributes.state == ObjectState::Sliding)
         {
            newAttributes.velocity.x = mAttributes.velocity.x * -1.f;
         }
      }
      else if (mAttributes.rect.getRight() <= c.x)
      {
         newAttributes.rect.left = c.x - newAttributes.rect.width;
         if (mAttributes.state == ObjectState::Flying ||
            mAttributes.state == ObjectState::Sliding)
         {
            newAttributes.velocity.x = mAttributes.velocity.x * -1.f;
         }
      }
      else
      {
         if (mAttributes.rect.getCenter().y > d.y)
         {
            newAttributes.rect.top = d.y;
            if (GRAVITY < 0.f)
            {
               if ((platformSegment.type == jp::physics::PlatformType::Ordinary ||
                  platformSegment.type == jp::physics::PlatformType::Sticky))
               {
                  newAttributes.state = ObjectState::Standing;
                  if (mAttributes.state == ObjectState::Flying)
                  {
                     newAttributes.velocity.x = 0.f;
                  }
               }
               else
               {
                  newAttributes.state = ObjectState::Sliding;
               }
            }
            else
            {
               newAttributes.state = ObjectState::Flying;
            }
         }
         else
         {
            newAttributes.rect.top = c.y - newAttributes.rect.height;
            //bounce or stay depends on gravity sign
            if (GRAVITY > 0.f)
            {
               if ((platformSegment.type == jp::physics::PlatformType::Ordinary ||
                  platformSegment.type == jp::physics::PlatformType::Sticky))
               {
                  newAttributes.state = ObjectState::Standing;
                  if (mAttributes.state == ObjectState::Flying)
                  {
                     newAttributes.velocity.x = 0.f;
                  }
               }
               else if (platformSegment.type == jp::physics::PlatformType::Slippery)
               {
                  newAttributes.state = ObjectState::Sliding;
               }
            }
            else
            {
               newAttributes.state = ObjectState::Flying;
            }
         }
      }
      newAttributes.velocity.y = 0.f;
      return true;
   }
   return false;
}

bool Object::checkDiagonalCollision(const jp::math::Segment<float>& objectSegment,
   const jp::physics::PlatformSegment& platformSegment, Attributes& newAttributes) const
{
   const jp::math::Vector2<float>& a = objectSegment.a.x < objectSegment.b.x ? objectSegment.a : objectSegment.b;
   const jp::math::Vector2<float>& b = objectSegment.a.x < objectSegment.b.x ? objectSegment.b : objectSegment.a;
   const jp::math::Vector2<float>& c = platformSegment.segment.a.x < platformSegment.segment.b.x ? platformSegment.segment.a : platformSegment.segment.b;
   const jp::math::Vector2<float>& d = platformSegment.segment.a.x < platformSegment.segment.b.x ? platformSegment.segment.b : platformSegment.segment.a;

   float slope = (d.y - c.y) / (d.x - c.x);
   float intercept = d.y - slope * d.x;
   float commonX = (a.y - intercept) / slope;

   if(commonX >= a.x && commonX <= b.x && commonX >= c.x && commonX <= d.x)
   {
      if (newAttributes.rect.getCenter().y > a.y)
      {
         if (slope > 0.f)
         {
            newAttributes.rect.top = std::min(d.y, std::max(a.x, b.x) + slope * intercept);
         }
         else
         {
            newAttributes.rect.top = std::min(c.y, (std::min(a.x, b.x) + slope * intercept) * slope);
         }
      }
      else
      {
         if (slope > 0.f)
         {
            newAttributes.rect.top = std::max(c.y, std::min(a.x, b.x) + slope * intercept) - newAttributes.rect.height;
         }
         else
         {
            newAttributes.rect.top = std::max(d.y, (std::max(a.x, b.x) + slope * intercept) * slope) - newAttributes.rect.height;
         }
      }
      newAttributes.velocity = { 150.f * slope, 150.f };
      return true;
   }
   return false;
}