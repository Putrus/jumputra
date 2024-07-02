#include "../../../logic/inc/Entity.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(EntityTest, DefaultConstructor)
   {
      Entity entity;
      EXPECT_EQ(math::Vector2<float>(), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(), entity.getRect());
      EXPECT_EQ(math::Vector2<float>(), entity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(), entity.getVelocity());
   }

   TEST(EntityTest, ArgumentsConstructor)
   {
      Entity entity(math::Rect<float>(1.f, 2.f, 3.f, 4.f),
         math::Vector2<float>(5.f, 6.f), math::Vector2<float>(7.f, 8.f));
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 3.f, 4.f), entity.getRect());
      EXPECT_EQ(math::Vector2<float>(5.f, 6.f), entity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(7.f, 8.f), entity.getVelocity());
   }

   TEST(EntityTest, SetPosition)
   {
      Entity entity;
      entity.setPosition(math::Vector2<float>(1.f, 3.f));
      EXPECT_EQ(math::Vector2<float>(1.f, 3.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 3.f, 0.f, 0.f), entity.getRect());
   }
}