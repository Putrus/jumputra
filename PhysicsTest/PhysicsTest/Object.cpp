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

   for (const auto& platform : platforms)
   {
      for (size_t startIdx = 0; startIdx < platform.mPoints.size(); ++startIdx)
      {
         size_t endIdx = (startIdx + 1) % platform.mPoints.size();
         //start segment point
         const jp::math::Vector2<float>& a = platform.mPoints[startIdx];
         //end segment point
         const jp::math::Vector2<float>& b = platform.mPoints[endIdx];
         //vertical segment
         if (a.x == b.x)
         {
            //for vertical segment we take into account only rect's horizontal segments
            if (jp::math::segmentsIntersect(newRect.getLeftTop(), newRect.getRightTop(), a, b) ||
               jp::math::segmentsIntersect(newRect.getRightBottom(), newRect.getLeftBottom(), a, b))
            {
               if (a.x < mRect.getCenter().x)
               {
                  newRect.left = a.x;
               }
               else
               {
                  newRect.left = a.x - newRect.width;
               }
               //bounce only if object skates or is in air
               if (mState == ObjectState::Sliding || mState== ObjectState::Flying)
               {
                  mVelocity.x = -mVelocity.x * BOUNCE_FACTOR;
                  mState = ObjectState::Bouncing;
               }
               break;
            }
         }
         else if (a.y == b.y)
         {
            //for horizontal segment we take into account only rect's vertical segments
            if (jp::math::segmentsIntersect(newRect.getRightTop(), newRect.getRightBottom(), a, b) ||
               jp::math::segmentsIntersect(newRect.getLeftBottom(), newRect.getLeftTop(), a, b))
            {
               if (a.y < mRect.getCenter().y)
               {
                  newRect.top = a.y;
                  //bounce or stay depends on gravity sign
                  if (GRAVITY > 0.f)
                  {
                     mVelocity.y = -mVelocity.y * BOUNCE_FACTOR;
                     mState = ObjectState::Bouncing;
                  }
                  else
                  {
                     mVelocity.y = 0.f;
                     mState = ObjectState::Standing;
                  }
               }
               else
               {
                  newRect.top = a.y - newRect.height;
                  //bounce or stay depends on gravity sign
                  if (GRAVITY < 0.f)
                  {
                     mVelocity.y = -mVelocity.y * BOUNCE_FACTOR;
                     mState = ObjectState::Bouncing;
                  }
                  else
                  {
                     mVelocity.y = 0.f;
                     mState = ObjectState::Standing;
                  }
               }
               /*if (platform.mType == jp::physics::SurfaceType::Slippery)
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
               }*/
            }
         }
         else
         {
            if (jp::math::segmentsIntersect(newRect.getLeftTop(), newRect.getRightTop(), a, b) ||
               jp::math::segmentsIntersect(newRect.getRightBottom(), newRect.getLeftBottom(), a, b))
            {
               newRect.top = mRect.top;
               mVelocity.x = mVelocity.y = 200.f;
               if ((a.x < b.x && a.y > b.y) || (a.x > b.x && a.y < b.y))
               {
                  mVelocity.x = -mVelocity.y;
               }
               newRect.left += mVelocity.x * seconds;
               newRect.top += mVelocity.y * seconds;
               break;
            }
         }
      }
   }

   mRect = newRect;
   mVelocity.x = mVelocity.x + (mAcceleration.x + WIND) * seconds;
   mVelocity.y = mVelocity.y + (mAcceleration.x + GRAVITY) * seconds;
}

//to do
//plan jest taki, ¿e checkCollision jest typu const i wyznacza newRect oraz zwraca nowy stan obiektu
//jeœli nie ma ¿adnej kolizji no to zwraca stan Flying
//zastanowiæ siê te¿ muszê nad stanem Bouncing. Mo¿e powinno byæ coœ w stylu "Falling" jeœli to jest w powietrzu
//a w sumie na ziemi po odbiciu to dalej jest sliding, tak¿e bouncing jest do wywalenia prawdopodobnie
//perfekcyjnie to siê zgrywa, bo jak jest falling a potem sliding no to nie mo¿emy podnieœæ obiektu. Trzeba by by³o dodaæ coœ w stylu DeadlySliding

//ObjectState Object::checkCollision(const std::vector<jp::physics::Platform>& platforms, jp::math::Rect<float>& newRect) const
//{
//
//   return ObjectState::Sliding;
//}

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