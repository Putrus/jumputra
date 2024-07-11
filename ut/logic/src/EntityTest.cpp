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

   TEST(EntityTest, Update)
   {
      Entity entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f),
         math::Vector2<float>(5.f, 10.f), math::Vector2<float>(5.f, 10.f));

      entity.update(1.f);
      EXPECT_EQ(math::Vector2<float>(12.5f, 25.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(12.5f, 25.f, 24.f, 24.f), entity.getRect());
      EXPECT_EQ(math::Vector2<float>(5.f, 10.f), entity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), entity.getVelocity());
   }

   TEST(EntityTest, FromJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.5,
               "top": 2.5,
               "width": 4.5,
               "height": 5.5
            },
            "acceleration": {
               "x": 6.5,
               "y": 12.5
            },
            "velocity": {
               "x": 13.5,
               "y": 25.125
            }
         }
         )");

      Entity entity;
      ASSERT_NO_THROW(entity.fromJson(json));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.5f, 2.5f, 4.5f, 5.5f), entity.getRect());
      EXPECT_EQ(math::Vector2<float>(6.5f, 12.5f), entity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(13.5f, 25.125f), entity.getVelocity());
   }

   TEST(EntityTest, FromJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "dect": {
               "left": 1.5,
               "top": 2.5,
               "width": 4.5,
               "height": 5.5
            },
            "acceleration": {
               "x": 6.5,
               "y": 12.5
            },
            "velocity": {
               "x": 13.5,
               "y": 25.125
            }
         }
         )");

      Entity entity;
      ASSERT_ANY_THROW(entity.fromJson(json));
   }

   TEST(EntityTest, ToJson)
   {
      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 5,
               "top": 10,
               "width": 24,
               "height": 24
            },
            "acceleration": {
               "x": 5.5,
               "y": 10.5
            },
            "velocity": {
               "x": 5,
               "y": 10
            }
         }
         )");

      Entity entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f),
         math::Vector2<float>(5.5f, 10.5f), math::Vector2<float>(5.f, 10.f));

      nlohmann::json actualJson = entity.toJson();
      EXPECT_EQ(expectedJson, actualJson);
   }

   TEST(EntityTest, SetPositionTwoArguments)
   {
      Entity entity;
      entity.setPosition(1.f, 3.f);
      EXPECT_EQ(math::Vector2<float>(1.f, 3.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 3.f, 0.f, 0.f), entity.getRect());
   }

   TEST(EntityTest, SetPositionOneArgument)
   {
      Entity entity;
      entity.setPosition(math::Vector2<float>(1.f, 3.f));
      EXPECT_EQ(math::Vector2<float>(1.f, 3.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 3.f, 0.f, 0.f), entity.getRect());
   }

   TEST(EntityTest, SetRect)
   {
      Entity entity;
      entity.setRect(math::Rect<float>(2.f, 4.f, 12.f, 24.f));
      EXPECT_EQ(math::Vector2<float>(2.f, 4.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(2.f, 4.f, 12.f, 24.f), entity.getRect());
   }

   TEST(EntityTest, SetRectTop)
   {
      Entity entity;
      entity.setRectTop(15.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 15.5f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(0.f, 15.5f, 0.f, 0.f), entity.getRect());
   }

   TEST(EntityTest, SetRectBottom)
   {
      Entity entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      entity.setRectBottom(25.5f);
      EXPECT_EQ(math::Vector2<float>(5.f, 1.5f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(5.f, 1.5f, 24.f, 24.f), entity.getRect());
   }

   TEST(EntityTest, SetRectLeft)
   {
      Entity entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      entity.setRectLeft(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 10.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(3.5f, 10.f, 24.f, 24.f), entity.getRect());
   }

   TEST(EntityTest, SetRectRight)
   {
      Entity entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      entity.setRectRight(26.5f);
      EXPECT_EQ(math::Vector2<float>(2.5f, 10.f), entity.getPosition());
      EXPECT_EQ(math::Rect<float>(2.5f, 10.f, 24.f, 24.f), entity.getRect());
   }

   TEST(EntityTest, SetAcceleration)
   {
      Entity entity;
      entity.setAcceleration(math::Vector2<float>(1.5f, 2.5f));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), entity.getAcceleration());
   }

   TEST(EntityTest, SetAccelerationX)
   {
      Entity entity;
      entity.setAccelerationX(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 0.f), entity.getAcceleration());
   }

   TEST(EntityTest, SetAccelerationY)
   {
      Entity entity;
      entity.setAccelerationY(4.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 4.5f), entity.getAcceleration());
   }

   TEST(EntityTest, SetVelocity)
   {
      Entity entity;
      entity.setVelocity(math::Vector2<float>(1.5f, 2.5f));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), entity.getVelocity());
   }

   TEST(EntityTest, SetVelocityX)
   {
      Entity entity;
      entity.setVelocityX(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 0.f), entity.getVelocity());
   }

   TEST(EntityTest, SetVelocityY)
   {
      Entity entity;
      entity.setVelocityY(4.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 4.5f), entity.getVelocity());
   }
}