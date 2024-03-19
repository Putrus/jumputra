#include "../../../../game/physics/inc/Segment.hpp"

#include <gtest/gtest.h>

namespace jp::ut::game::physics
{
   class SegmentTest : public testing::Test
   {
   protected:
      void SetUp() override {}

      void TearDown() override
      {
         delete mSegment;
         mSegment = nullptr;
      }

      jp::game::physics::Segment* mSegment = nullptr;
   };
}