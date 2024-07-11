#include "../inc/EntityTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST_F(EntityTest, DefaultConstructor)
   {
      EXPECT_EQ(math::Vector2<float>(), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(), mEntity.getRect());
      EXPECT_EQ(math::Vector2<float>(), mEntity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(), mEntity.getVelocity());
   }

   TEST_F(EntityTest, ArgumentsConstructor)
   {
      mEntity = Entity(math::Rect<float>(1.f, 2.f, 3.f, 4.f),
         math::Vector2<float>(5.f, 6.f), math::Vector2<float>(7.f, 8.f));
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 3.f, 4.f), mEntity.getRect());
      EXPECT_EQ(math::Vector2<float>(5.f, 6.f), mEntity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(7.f, 8.f), mEntity.getVelocity());
   }

   TEST_F(EntityTest, Update)
   {
      mEntity = Entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f),
         math::Vector2<float>(5.f, 10.f), math::Vector2<float>(5.f, 10.f));

      mEntity.update(1.f);
      EXPECT_EQ(math::Vector2<float>(12.5f, 25.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(12.5f, 25.f, 24.f, 24.f), mEntity.getRect());
      EXPECT_EQ(math::Vector2<float>(5.f, 10.f), mEntity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), mEntity.getVelocity());
   }

   TEST_F(EntityTest, FromJson)
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

      ASSERT_NO_THROW(mEntity.fromJson(json));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.5f, 2.5f, 4.5f, 5.5f), mEntity.getRect());
      EXPECT_EQ(math::Vector2<float>(6.5f, 12.5f), mEntity.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(13.5f, 25.125f), mEntity.getVelocity());
   }

   TEST_F(EntityTest, FromJsonWrongJson)
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

      ASSERT_ANY_THROW(mEntity.fromJson(json));
   }

   TEST_F(EntityTest, ToJson)
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

      mEntity = Entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f),
         math::Vector2<float>(5.5f, 10.5f), math::Vector2<float>(5.f, 10.f));

      nlohmann::json actualJson = mEntity.toJson();
      EXPECT_EQ(expectedJson, actualJson);
   }

   TEST_F(EntityTest, SetPositionTwoArguments)
   {
      mEntity.setPosition(1.f, 3.f);
      EXPECT_EQ(math::Vector2<float>(1.f, 3.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 3.f, 0.f, 0.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetPositionOneArgument)
   {
      mEntity.setPosition(math::Vector2<float>(1.f, 3.f));
      EXPECT_EQ(math::Vector2<float>(1.f, 3.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 3.f, 0.f, 0.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetRect)
   {
      mEntity.setRect(math::Rect<float>(2.f, 4.f, 12.f, 24.f));
      EXPECT_EQ(math::Vector2<float>(2.f, 4.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(2.f, 4.f, 12.f, 24.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetRectTop)
   {
      mEntity.setRectTop(15.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 15.5f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(0.f, 15.5f, 0.f, 0.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetRectBottom)
   {
      mEntity = Entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      mEntity.setRectBottom(25.5f);
      EXPECT_EQ(math::Vector2<float>(5.f, 1.5f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(5.f, 1.5f, 24.f, 24.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetRectLeft)
   {
      mEntity = Entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      mEntity.setRectLeft(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 10.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(3.5f, 10.f, 24.f, 24.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetRectRight)
   {
      mEntity = Entity(math::Rect<float>(5.f, 10.f, 24.f, 24.f));
      mEntity.setRectRight(26.5f);
      EXPECT_EQ(math::Vector2<float>(2.5f, 10.f), mEntity.getPosition());
      EXPECT_EQ(math::Rect<float>(2.5f, 10.f, 24.f, 24.f), mEntity.getRect());
   }

   TEST_F(EntityTest, SetAcceleration)
   {
      mEntity.setAcceleration(math::Vector2<float>(1.5f, 2.5f));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), mEntity.getAcceleration());
   }

   TEST_F(EntityTest, SetAccelerationX)
   {
      mEntity.setAccelerationX(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 0.f), mEntity.getAcceleration());
   }

   TEST_F(EntityTest, SetAccelerationY)
   {
      mEntity.setAccelerationY(4.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 4.5f), mEntity.getAcceleration());
   }

   TEST_F(EntityTest, SetVelocity)
   {
      mEntity.setVelocity(math::Vector2<float>(1.5f, 2.5f));
      EXPECT_EQ(math::Vector2<float>(1.5f, 2.5f), mEntity.getVelocity());
   }

   TEST_F(EntityTest, SetVelocityX)
   {
      mEntity.setVelocityX(3.5f);
      EXPECT_EQ(math::Vector2<float>(3.5f, 0.f), mEntity.getVelocity());
   }

   TEST_F(EntityTest, SetVelocityY)
   {
      mEntity.setVelocityY(4.5f);
      EXPECT_EQ(math::Vector2<float>(0.f, 4.5f), mEntity.getVelocity());
   }
}