#include "Object.h"
#include "Functions.h"

#include <algorithm>
#include <iostream>

Object::Object(const jp::math::Rect<float>& rect, const jp::math::Vector2<float>& velocity, const jp::math::Vector2<float>& acceleration)
   : mRect(rect), mVelocity(velocity), mAcceleration(acceleration)
{}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   sf::Color color = sf::Color::Red;
   sf::VertexArray rectangle(sf::Quads, 4);
   rectangle[0] = sf::Vertex({ mRect.left, mRect.top }, color);
   rectangle[1] = sf::Vertex({ mRect.getRight(), mRect.top}, color);
   rectangle[2] = sf::Vertex({ mRect.getRight(), mRect.getBottom()}, color);
   rectangle[3] = sf::Vertex({ mRect.left, mRect.getBottom() }, color);
   target.draw(rectangle, states);
}

void Object::update(float seconds, const std::vector<jp::physics::Platform>& platforms)
{
   jp::math::Rect<float> newRect = getRect();
   newRect.left += mVelocity.x * seconds + ((mAcceleration.x + WIND) * seconds * seconds) / 2.f;
   newRect.top += mVelocity.y * seconds + ((mAcceleration.y + GRAVITY) * seconds * seconds) / 2.f;

   /*jp::math::Vector2<float> dir1 = newRect.getRightTop() - newRect.getLeftTop();
   jp::math::Vector2<float> dir2 = newRect.getLeftTop() - newRect.getRightBottom();
   jp::math::Vector2<float> dir3 = newRect.getRightBottom() - newRect.getLeftBottom();
   jp::math::Vector2<float> dir4 = newRect.getLeftBottom() - newRect.getLeftTop();*/
   for (const auto& platform : platforms)
   {
      for (size_t i = 0; i < platform.mPoints.size(); ++i)
      {
         size_t next = (i == platform.mPoints.size() - 1) ? 0 : i + 1;

         const jp::math::Vector2<float>& a = platform.mPoints[i];
         const jp::math::Vector2<float>& b = platform.mPoints[next];
         float bounceFactor = 0.5f;
         if (a.x == b.x)
         {
            //for vertical segment we take into account only rect's horizontal segments
            if (jp::math::intersects(newRect.getLeftTop(), newRect.getRightTop(), a, b) ||
               jp::math::intersects(newRect.getRightBottom(), newRect.getLeftBottom(), a, b))
            {
               if (a.x < mRect.getCenter().x)
               {
                  newRect.left = a.x;
               }
               else
               {
                  newRect.left = a.x - newRect.width;
               }
               mVelocity.x = -mVelocity.x * bounceFactor;
            }
            
         }
         else if (a.y == b.y)
         {
            //for horizontal segment we take into account only rect's vertical segments
            if (jp::math::intersects(newRect.getRightTop(), newRect.getRightBottom(), a, b) ||
               jp::math::intersects(newRect.getLeftBottom(), newRect.getLeftTop(), a, b))
            {
               if (a.y < mRect.getCenter().y)
               {
                  newRect.top = a.y;
                  //bounce or stay depends on gravity sign
                  mVelocity.y = mAcceleration.y > 0.f ? -mVelocity.y * bounceFactor : 0;
               }
               else
               {
                  newRect.top = a.y - newRect.height;
                  //bounce or stay depends on gravity sign
                  mVelocity.y = mAcceleration.y < 0.f ? -mVelocity.y * bounceFactor : 0;
               }
               if (platform.mType == jp::physics::SurfaceType::Slippery)
               {
                  newRect.top = mRect.top;
                  mVelocity.y = 0;
                  if (mVelocity.x > 5.f || mVelocity.x < -5.f)
                  {
                     mAcceleration.x = -mVelocity.x;
                  }
                  else
                  {
                     mAcceleration.x = 0.f;
                     mVelocity.x = 0.f;
                  }
               }
            }
         }
         else
         {
            if (jp::math::intersects(newRect.getLeftTop(), newRect.getRightTop(), a, b) ||
               jp::math::intersects(newRect.getRightBottom(), newRect.getLeftBottom(), a, b))
            {
               newRect.top = mRect.top;
               mVelocity.x = mVelocity.y = 200.f;
               if ((a.x < b.x && a.y > b.y) || (a.x > b.x && a.y < b.y))
               {
                  mVelocity.x = -mVelocity.y;
               }
                  std::cout << "diagonal" << std::endl;
               newRect.left += mVelocity.x * seconds;
               newRect.top += mVelocity.y * seconds;
            }
         }
      }
   }

   mRect = newRect;
   mVelocity.x = mVelocity.x + (mAcceleration.x + WIND) * seconds;
   mVelocity.y = mVelocity.y + (mAcceleration.x + GRAVITY) * seconds;
}

jp::math::Rect<float> Object::getRect() const
{
   return mRect;
}

void Object::log()
{
   std::cout << "Pos = " << mRect.getPosition() << std::endl;
   std::cout << "A = " << mAcceleration << std::endl;
   std::cout << "V = " << mVelocity << std::endl;
}