#pragma once

#include "../../../logic/inc/Entity.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class EntityTest : public testing::Test
   {
   protected:
      void SetUp() override
      {
         mEntity = jp::logic::Entity();
      }

      void TearDown() override {}

      jp::logic::Entity mEntity;
   };
}