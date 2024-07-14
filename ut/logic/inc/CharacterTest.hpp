#pragma once

#include "../../../logic/inc/Character.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class CharacterTest : public testing::Test
   {
   protected:
      void SetUp() override
      {
         mProperties.secondsPerUpdate = 0.015625f;
         mProperties.character.jump.gain.x = 0.f;
         mProperties.character.jump.gain.y = 1000.f;
         mProperties.character.jump.max.x = 195.f;
         mProperties.character.jump.max.y = 500.f;
         mProperties.character.runSpeed = 85.f;
         mProperties.character.size.x = 24.f;
         mProperties.character.size.y = 24.f;

         mProperties.physics.bounceFactor = 0.5f;
         mProperties.physics.checkCollisionDistance = 600.f;
         mProperties.physics.fallSpeed = 500.f;
         mProperties.physics.slipperyFriction = 200.f;
         mProperties.physics.gravity.x = 0.f;
         mProperties.physics.gravity.y = 800.f;

         mStatistics.falls = 0;
         mStatistics.jumps = 0;
         mStatistics.time = 0.f;

         mCharacter = std::make_shared<jp::logic::Character>(math::Rect<float>(), mProperties, mStatistics, mSegments, mWinds);
      }

      void TearDown() override {}

      std::shared_ptr<jp::logic::Character> mCharacter;
      jp::logic::Properties mProperties;
      jp::logic::Statistics mStatistics;
      std::vector<std::shared_ptr<jp::logic::Segment>> mSegments;
      std::vector<std::shared_ptr<jp::logic::Wind>> mWinds;
   };
}