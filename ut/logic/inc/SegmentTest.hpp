#include "../../../logic/inc/Segment.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
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

      jp::logic::Segment* mSegment = nullptr;
   };
}