#include "../../../logic/inc/Properties.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(PropertiesTest, FromJson)
   {
      Properties properties;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "secondsPerUpdate" : 0.0167,
            "character": {
               "jump": {
                  "gain": {
                     "x": 0.0,
                     "y": 1000.0
                  },
                  "max": {
                     "x": 195.0,
                     "y": 500.0
                  }
               },
               "runSpeed": 85.0,
               "size": {
                  "x": 24.0,
                  "y": 24.0
               }
            },
            "physics": {
               "bounceFactor": 0.5,
               "checkCollisionDistance": 600.0,
               "fallSpeed": 500.0,
               "slipperyFriction": 200.0,
               "gravity": {
                  "x" : 0.0,
                  "y" : 800.0
               }
            }
         }
         )");

      ASSERT_NO_THROW(properties.fromJson(json));
      EXPECT_EQ(0.0167f, properties.secondsPerUpdate);

      EXPECT_EQ(0.f, properties.character.jump.gain.x);
      EXPECT_EQ(1000.f, properties.character.jump.gain.y);
      EXPECT_EQ(195.f, properties.character.jump.max.x);
      EXPECT_EQ(500.f, properties.character.jump.max.y);

      EXPECT_EQ(85.f, properties.character.runSpeed);
      EXPECT_EQ(24.f, properties.character.size.x);
      EXPECT_EQ(24.f, properties.character.size.y);

      EXPECT_EQ(0.5f, properties.physics.bounceFactor);
      EXPECT_EQ(600.f, properties.physics.checkCollisionDistance);
      EXPECT_EQ(500.f, properties.physics.fallSpeed);
      EXPECT_EQ(200.f, properties.physics.slipperyFriction);
      EXPECT_EQ(0.f, properties.physics.gravity.x);
      EXPECT_EQ(800.f, properties.physics.gravity.y);
   }

   TEST(PropertiesTest, FromJsonWrongJson)
   {
      Properties properties;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "secondsPerUpdate" : 0.0167,
            "sharacter": {
               "jump": {
                  "gain": {
                     "x": 0.0,
                     "y": 1000.0
                  },
                  "max": {
                     "x": 195.0,
                     "y": 500.0
                  }
               },
               "runSpeed": 85.0,
               "size": {
                  "x": 24.0,
                  "y": 24.0
               }
            },
            "dhysics": {
               "bounceFactor": 0.5,
               "checkCollisionDistance": 600.0,
               "fallSpeed": 500.0,
               "slipperyFriction": 200.0,
               "rravity": {
                  "x" : 0.0,
                  "y" : 800.0
               }
            }
         }
         )");

      ASSERT_ANY_THROW(properties.fromJson(json));
   }

   TEST(PropertiesTest, ToJson)
   {
      Properties properties;

      properties.secondsPerUpdate = 1.5f;
      properties.character.jump.gain.x = 0.f;
      properties.character.jump.gain.y = 1000.f;
      properties.character.jump.max.x = 195.f;
      properties.character.jump.max.y = 500.f;
      properties.character.runSpeed = 85.f;
      properties.character.size.x = 24.f;
      properties.character.size.y = 24.f;

      properties.physics.bounceFactor = 2.5f;
      properties.physics.checkCollisionDistance = 600.f;
      properties.physics.fallSpeed = 500.f;
      properties.physics.slipperyFriction = 200.f;
      properties.physics.gravity.x = 0.f;
      properties.physics.gravity.y = 800.f;

      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "secondsPerUpdate" : 1.5,
            "character": {
               "jump": {
                  "gain": {
                     "x": 0.0,
                     "y": 1000.0
                  },
                  "max": {
                     "x": 195.0,
                     "y": 500.0
                  }
               },
               "runSpeed": 85.0,
               "size": {
                  "x": 24.0,
                  "y": 24.0
               }
            },
            "physics": {
               "bounceFactor": 2.5,
               "checkCollisionDistance": 600.0,
               "fallSpeed": 500.0,
               "slipperyFriction": 200.0,
               "gravity": {
                  "x" : 0.0,
                  "y" : 800.0
               }
            }
         }
         )");

      nlohmann::json actualJson = properties.toJson();

      EXPECT_EQ(expectedJson, actualJson);
   }
}