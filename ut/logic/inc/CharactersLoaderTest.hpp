#pragma once

#include "../../../logic/inc/Character.hpp"
#include "../../../logic/inc/CharactersLoader.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class CharactersLoaderTest : public testing::Test
   {
   protected:
      void SetUp() override
      {
         mLoader = new jp::logic::CharactersLoader<jp::logic::Character>(mProperties, mSegments, mWinds);
      }

      void TearDown() override
      {
         delete mLoader;
         mLoader = nullptr;
      }

      jp::logic::CharactersLoader<jp::logic::Character>* mLoader;

      jp::logic::Properties mProperties;
      std::vector<std::shared_ptr<jp::logic::Segment>> mSegments;
      std::vector<std::shared_ptr<jp::logic::Wind>> mWinds;
   };
}