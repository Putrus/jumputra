#include "../inc/CharactersLoaderTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST_F(CharactersLoaderTest, NoCharacters)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "characters": []
         }
      )");
      auto characters = mLoader->loadFromJson(json);
      EXPECT_EQ(0, characters.size());
   }

   TEST_F(CharactersLoaderTest, OneCharacter)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "characters": [
               {
                  "rect": {
                     "left": 10.0,
                     "top": 20.0,
                     "width": 30.0,
                     "height": 40.0
                  },
                  "acceleration": {
                     "x": 10.0,
                     "y": 20.0
                  },
                  "velocity": {
                     "x": 10.0,
                     "y": 20.0
                  },
                  "state": 3,
                  "direction": 1,
                  "jumpPower": {
                     "x": 10.0,
                     "y": 20.0
                  },
                  "gravity": {
                     "x": 10.0,
                     "y": 20.0
                  },
                  "runSpeed": 10.0,
                  "statistics": {
                     "jumps": 10,
                     "falls": 20,
                     "time": 30.0
                  }
               }
            ]
         }
      )");
      auto characters = mLoader->loadFromJson(json);
      ASSERT_EQ(1, characters.size());
      EXPECT_EQ(10.f, characters.at(0)->getRect().left);
      EXPECT_EQ(20.f, characters.at(0)->getRect().left);
      EXPECT_EQ(30.f, characters.at(0)->getRect().width);
      EXPECT_EQ(40.f, characters.at(0)->getRect().height);

      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), characters.at(0)->getAcceleration());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), characters.at(0)->getVelocity());
      EXPECT_EQ(CharacterState::Flying, characters.at(0)->getState());
      EXPECT_EQ(CharacterDirection::Left, characters.at(0)->getDirection());
      EXPECT_EQ(10.f, characters.at(0)->getRunSpeed());
      EXPECT_EQ(10, characters.at(0)->getStatistics().jumps);
      EXPECT_EQ(20, characters.at(0)->getStatistics().falls);
      EXPECT_EQ(30.f, characters.at(0)->getStatistics().time);
   }
}