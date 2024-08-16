#include "../inc/CharacterTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST_F(CharacterTest, ConstructorSixArguments)
   {
      mCharacter = std::make_shared<Character>(math::Vector2<float>(1.f, 2.f), math::Vector2<float>(24.f, 24.f),
         mProperties, mStatistics, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(), mCharacter->getAcceleration());
      EXPECT_EQ(CharacterDirection::Up, mCharacter->getDirection());
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mCharacter->getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 24.f, 24.f), mCharacter->getRect());
      EXPECT_EQ(0.f, mCharacter->getRunSpeed());
      EXPECT_EQ(CharacterState::Flying, mCharacter->getState());
      EXPECT_EQ(0, mCharacter->getStatistics().falls);
      EXPECT_EQ(0, mCharacter->getStatistics().jumps);
      EXPECT_EQ(0.f, mCharacter->getStatistics().time);
      EXPECT_EQ(math::Vector2<float>(), mCharacter->getVelocity());
   }

   TEST_F(CharacterTest, ConstructorFiveArguments)
   {
      mCharacter = std::make_shared<Character>(math::Rect<float>(1.f, 2.f, 24.f, 24.f),
         mProperties, mStatistics, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(), mCharacter->getAcceleration());
      EXPECT_EQ(CharacterDirection::Up, mCharacter->getDirection());
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mCharacter->getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 24.f, 24.f), mCharacter->getRect());
      EXPECT_EQ(0.f, mCharacter->getRunSpeed());
      EXPECT_EQ(CharacterState::Flying, mCharacter->getState());
      EXPECT_EQ(0, mCharacter->getStatistics().falls);
      EXPECT_EQ(0, mCharacter->getStatistics().jumps);
      EXPECT_EQ(0.f, mCharacter->getStatistics().time);
      EXPECT_EQ(math::Vector2<float>(), mCharacter->getVelocity());
   }

   TEST_F(CharacterTest, ConstructorJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "velocity": {
               "x": 5.5,
               "y": 6.25
            },
            "state": 3,
            "direction": 1,
            "jumpPower": {
               "x": 6.5,
               "y": 7.5
            },
            "gravity": {
               "x": 4.25,
               "y": 8.25
            },
            "runSpeed": 2.25,
            "statistics": {
               "jumps": 1,
               "falls": 2,
               "time": 6.5,
               "totalTime": 5.75
            }
         }
         )");
      ASSERT_NO_THROW(mCharacter = std::make_shared<Character>(json,
         mProperties, mStatistics, mSegments, mWinds));

      EXPECT_EQ(math::Vector2<float>(2.5f, 3.5f), mCharacter->getAcceleration());
      EXPECT_EQ(CharacterDirection::Left, mCharacter->getDirection());
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mCharacter->getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 24.f, 24.f), mCharacter->getRect());
      EXPECT_EQ(2.25f, mCharacter->getRunSpeed());
      EXPECT_EQ(CharacterState::Flying, mCharacter->getState());
      EXPECT_EQ(2, mCharacter->getStatistics().falls);
      EXPECT_EQ(1, mCharacter->getStatistics().jumps);
      EXPECT_EQ(6.5f, mCharacter->getStatistics().time);
      EXPECT_EQ(math::Vector2<float>(5.5f, 6.25f), mCharacter->getVelocity());
   }

   TEST_F(CharacterTest, ConstructorJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "dupelocity": {
               "x": 5.5,
               "y": 6.25
            }
         }
         )");
      ASSERT_ANY_THROW(mCharacter = std::make_shared<Character>(json,
         mProperties, mStatistics, mSegments, mWinds));
   }

   TEST_F(CharacterTest, Create)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "velocity": {
               "x": 5.5,
               "y": 6.25
            },
            "state": 3,
            "direction": 1,
            "jumpPower": {
               "x": 6.5,
               "y": 7.5
            },
            "gravity": {
               "x": 4.25,
               "y": 8.25
            },
            "runSpeed": 2.25,
            "statistics": {
               "jumps": 1,
               "falls": 2,
               "time": 6.5,
               "totalTime": 5.75
            }
         }
         )");
      ASSERT_NO_THROW(mCharacter = Character::create(json,
         mProperties, mStatistics, mSegments, mWinds));

      EXPECT_EQ(math::Vector2<float>(2.5f, 3.5f), mCharacter->getAcceleration());
      EXPECT_EQ(CharacterDirection::Left, mCharacter->getDirection());
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mCharacter->getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 24.f, 24.f), mCharacter->getRect());
      EXPECT_EQ(2.25f, mCharacter->getRunSpeed());
      EXPECT_EQ(CharacterState::Flying, mCharacter->getState());
      EXPECT_EQ(2, mCharacter->getStatistics().falls);
      EXPECT_EQ(1, mCharacter->getStatistics().jumps);
      EXPECT_EQ(6.5f, mCharacter->getStatistics().time);
      EXPECT_EQ(math::Vector2<float>(5.5f, 6.25f), mCharacter->getVelocity());
   }

   TEST_F(CharacterTest, CreateWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "dupelocity": {
               "x": 5.5,
               "y": 6.25
            }
         }
         )");
      ASSERT_ANY_THROW(mCharacter = Character::create(json,
         mProperties, mStatistics, mSegments, mWinds));
   }

   TEST_F(CharacterTest, FromJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "velocity": {
               "x": 5.5,
               "y": 6.25
            },
            "state": 3,
            "direction": 1,
            "jumpPower": {
               "x": 6.5,
               "y": 7.5
            },
            "gravity": {
               "x": 4.25,
               "y": 8.25
            },
            "runSpeed": 2.25,
            "statistics": {
               "jumps": 1,
               "falls": 2,
               "time": 6.5,
               "totalTime": 5.75
            }
         }
         )");
      ASSERT_NO_THROW(mCharacter->fromJson(json));

      EXPECT_EQ(math::Vector2<float>(2.5f, 3.5f), mCharacter->getAcceleration());
      EXPECT_EQ(CharacterDirection::Left, mCharacter->getDirection());
      EXPECT_EQ(math::Vector2<float>(1.f, 2.f), mCharacter->getPosition());
      EXPECT_EQ(math::Rect<float>(1.f, 2.f, 24.f, 24.f), mCharacter->getRect());
      EXPECT_EQ(2.25f, mCharacter->getRunSpeed());
      EXPECT_EQ(CharacterState::Flying, mCharacter->getState());
      EXPECT_EQ(2, mCharacter->getStatistics().falls);
      EXPECT_EQ(1, mCharacter->getStatistics().jumps);
      EXPECT_EQ(6.5f, mCharacter->getStatistics().time);
      EXPECT_EQ(math::Vector2<float>(5.5f, 6.25f), mCharacter->getVelocity());
   }

   TEST_F(CharacterTest, FromJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.0,
               "top": 2.0,
               "width": 24.0,
               "height": 24.0
            },
            "acceleration": {
               "x": 2.5,
               "y": 3.5
            },
            "dupelocity": {
               "x": 5.5,
               "y": 6.25
            }
         }
         )");
      ASSERT_ANY_THROW(mCharacter->fromJson(json));
   }

   TEST_F(CharacterTest, ToJson)
   {
      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 0.0,
               "top": 0.0,
               "width": 0.0,
               "height": 0.0
            },
            "acceleration": {
               "x": 0.0,
               "y": 0.0
            },
            "velocity": {
               "x": 0.0,
               "y": 0.0
            },
            "state": 3,
            "direction": 0,
            "jumpPower": {
               "x": 0.0,
               "y": 0.0
            },
            "gravity": {
               "x": 0.0,
               "y": 0.0
            },
            "runSpeed": 0.0,
            "statistics": {
               "jumps": 0,
               "falls": 0,
               "time": 0.0,
               "totalTime": 0.0
            }
         }
         )");

      nlohmann::json actualJson = mCharacter->toJson();
      EXPECT_EQ(expectedJson, actualJson);
   }

   TEST(CharacterStateTest, OstreamOperatorBurying)
   {
      CharacterState state = CharacterState::Burying;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Burying", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorDying)
   {
      CharacterState state = CharacterState::Dying;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Dying", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorFalling)
   {
      CharacterState state = CharacterState::Falling;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Falling", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorFlying)
   {
      CharacterState state = CharacterState::Flying;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Flying", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorLying)
   {
      CharacterState state = CharacterState::Lying;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Lying", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorRunning)
   {
      CharacterState state = CharacterState::Running;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Running", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorSledding)
   {
      CharacterState state = CharacterState::Sledding;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Sledding", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorSliding)
   {
      CharacterState state = CharacterState::Sliding;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Sliding", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorSquatting)
   {
      CharacterState state = CharacterState::Squatting;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Squatting", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorStanding)
   {
      CharacterState state = CharacterState::Standing;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Standing", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorSticking)
   {
      CharacterState state = CharacterState::Sticking;

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Sticking", ss.str());
   }

   TEST(CharacterStateTest, OstreamOperatorUnknown)
   {
      CharacterState state = static_cast<CharacterState>(99);

      std::stringstream ss;
      ss << state;
      EXPECT_EQ("Unknown", ss.str());
   }
}