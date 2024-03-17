#include "../../../../game/physics/inc/Entity.hpp"

#include <gtest/gtest.h>

namespace jp::ut::game::physics
{
   using namespace jp::game::physics;

   TEST(Entity, DefaultConstructor)
   {
      Entity entity;
      EXPECT_EQ(math::Vector2<float>(), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(), entity.getRect());
      EXPECT_EQ(math::Vector2<float>(), entity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(), entity.getVelocity());
   }
}