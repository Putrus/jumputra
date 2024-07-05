#pragma once

#include "../../../logic/inc/Segment.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class SegmentTest : public testing::Test
   {
   protected:
      void SetUp() override {}

      void TearDown() override {}

      std::shared_ptr<jp::logic::Segment> mSegment = nullptr;
   };
}