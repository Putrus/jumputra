#include "../../../../game/physics/inc/WindUpdater.hpp"

#include <gtest/gtest.h>

namespace jp::ut::game::physics
{
   class WindUpdaterTest : public testing::Test
   {
      protected:
         void SetUp() override {}

         void TearDown() override {}

         jp::game::physics::WindUpdater mUpdater;
   };
}