#include "../../../logic/inc/Wind.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(WindTest, ArgumentsConstructor)
   {
      Wind wind(15.f, math::Vector2<float>(100.f, 100.f),
         math::Rect<float>(10.f, 15.f, 20.f, 25.f),
         math::Vector2<float>(5.f, 10.f),
         math::Vector2<float>(3.5f, 4.5f));

      EXPECT_EQ(15.f, wind.getImpact());
      EXPECT_EQ(math::Vector2<float>(100.f, 100.f), wind.getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(10.f, 15.f, 20.f, 25.f), wind.getRect());
      EXPECT_EQ(math::Vector2<float>(5.f, 10.f), wind.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(3.5f, 4.5f), wind.getVelocity());
   }

   TEST(WindTest, JsonConstructor)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "acceleration": {
               "x" : 100.0,
               "y" : 5.5
            },
            "impact" : 1.0,
            "maxVelocity" : {
               "x" : 500.0,
               "y" : 0.0
            },
            "rect": {
               "left" : 0.0,
               "top" : 4320.0,
               "width" : 480.0,
               "height" : 2160.0
            },
            "velocity": {
               "x": 4.5,
               "y": 5.5
            }
         }
         )");

      ASSERT_NO_THROW({ Wind wind(json);
         EXPECT_EQ(1.f, wind.getImpact());
         EXPECT_EQ(math::Vector2<float>(500.f, 0.f), wind.getMaxVelocity());
         EXPECT_EQ(math::Rect<float>(0.f, 4320.f, 480.f, 2160.f), wind.getRect());
         EXPECT_EQ(math::Vector2<float>(100.f, 5.5f), wind.getAcceleration());
         EXPECT_EQ(math::Vector2<float>(4.5f, 5.5f), wind.getVelocity());
      });
   }

   TEST(WindTest, JsonConstructorWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "bcceleration": {
               "x" : 100.0,
               "y" : 5.5
            },
            "impact" : 1.0,
            "maxVelocity" : {
               "x" : 500.0,
               "y" : 0.0
            },
            "rect": {
               "left" : 0.0,
               "top" : 4320.0,
               "width" : 480.0,
               "height" : 2160.0
            },
            "velocity": {
               "x": 4.5,
               "y": 5.5
            }
         }
         )");

      ASSERT_ANY_THROW({ Wind wind(json); });
   }

   TEST(WindTest, FromJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "acceleration": {
               "x" : 100.0,
               "y" : 5.5
            },
            "impact" : 1.0,
            "maxVelocity" : {
               "x" : 500.0,
               "y" : 0.0
            },
            "rect": {
               "left" : 0.0,
               "top" : 4320.0,
               "width" : 480.0,
               "height" : 2160.0
            },
            "velocity": {
               "x": 4.5,
               "y": 5.5
            }
         }
         )");

      Wind wind(0.f, {}, {}, 0.f);
      ASSERT_NO_THROW(wind.fromJson(json));
      EXPECT_EQ(1.f, wind.getImpact());
      EXPECT_EQ(math::Vector2<float>(500.f, 0.f), wind.getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 4320.f, 480.f, 2160.f), wind.getRect());
      EXPECT_EQ(math::Vector2<float>(100.f, 5.5f), wind.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(4.5f, 5.5f), wind.getVelocity());
   }

   TEST(WindTest, FromJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "dicceleration": {
               "x" : 100.0,
               "y" : 5.5
            },
            "impact" : 1.0,
            "maxVelocity" : {
               "x" : 500.0,
               "y" : 0.0
            },
            "rect": {
               "left" : 0.0,
               "top" : 4320.0,
               "width" : 480.0,
               "height" : 2160.0
            },
            "velocity": {
               "x": 4.5,
               "y": 5.5
            }
         }
         )");

      Wind wind(0.f, {}, {}, 0.f);
      ASSERT_ANY_THROW(wind.fromJson(json));
   }

   TEST(WindTest, Create)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "acceleration": {
               "x" : 6.5,
               "y" : 5.5
            },
            "impact" : 1.0,
            "maxVelocity" : {
               "x" : 500.0,
               "y" : 0.0
            },
            "rect": {
               "left" : 0.0,
               "top" : 4320.0,
               "width" : 480.0,
               "height" : 2160.0
            },
            "velocity": {
               "x": 4.5,
               "y": 5.5
            }
         }
         )");

      std::shared_ptr<Wind> wind = Wind::create(json);
      ASSERT_NO_THROW(wind->fromJson(json));
      EXPECT_EQ(1.f, wind->getImpact());
      EXPECT_EQ(math::Vector2<float>(500.f, 0.f), wind->getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 4320.f, 480.f, 2160.f), wind->getRect());
      EXPECT_EQ(math::Vector2<float>(6.5f, 5.5f), wind->getAcceleration());
      EXPECT_EQ(math::Vector2<float>(4.5f, 5.5f), wind->getVelocity());
   }

   TEST(WindTest, UpdateSimpleHorizontalVelocity)
   {
      Wind wind(15.f, math::Vector2<float>(500.f, 0.f),
         math::Rect<float>(0.f, 0.f, 20.f, 20.f),
         math::Vector2<float>(100.f, 0.f));

      wind.update(1.f);

      EXPECT_EQ(15.f, wind.getImpact());
      EXPECT_EQ(math::Vector2<float>(500.f, 0.f), wind.getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 20.f, 20.f), wind.getRect());
      EXPECT_EQ(math::Vector2<float>(100.f, 0.f), wind.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(100.f, 0.f), wind.getVelocity());
   }

   TEST(WindTest, UpdateMaxHorizontalVelocity)
   {
      Wind wind(15.f, math::Vector2<float>(500.f, 0.f),
         math::Rect<float>(0.f, 0.f, 20.f, 20.f),
         math::Vector2<float>(100.f, 0.f),
         math::Vector2<float>(450.f, 0.f));

      wind.update(1.f);

      EXPECT_EQ(15.f, wind.getImpact());
      EXPECT_EQ(math::Vector2<float>(-500.f, 0.f), wind.getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 20.f, 20.f), wind.getRect());
      EXPECT_EQ(math::Vector2<float>(-100.f, 0.f), wind.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(500.f, 0.f), wind.getVelocity());
   }

   TEST(WindTest, SetMaxVelocity)
   {
      Wind wind(25.f, math::Vector2<float>(500.f, 0.f),
         math::Rect<float>(0.f, 0.f, 20.f, 20.f),
         math::Vector2<float>(100.f, 0.f),
         math::Vector2<float>(450.f, 0.f));

      wind.setMaxVelocity(math::Vector2<float>(600.f, 700.f));

      EXPECT_EQ(25.f, wind.getImpact());
      EXPECT_EQ(math::Vector2<float>(600.f, 700.f), wind.getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 20.f, 20.f), wind.getRect());
      EXPECT_EQ(math::Vector2<float>(100.f, 0.f), wind.getAcceleration());
      EXPECT_EQ(math::Vector2<float>(450.f, 0.f), wind.getVelocity());
   }
}