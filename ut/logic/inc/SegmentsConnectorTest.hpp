#pragma once

#include "../../../logic/inc/SegmentsConnector.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class SegmentsConnectorTest : public testing::Test
   {
   protected:
      void SetUp() override {}

      void TearDown() override
      {
         mSegments.clear();
      }

      std::vector<std::shared_ptr<jp::logic::Segment>> mSegments;
   };
}