#include "../../../logic/inc/Character.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

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