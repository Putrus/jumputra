#include "../../../../game/physics/inc/BodyUpdater.hpp"
#include "../../../../game/physics/inc/HorizontalSegment.hpp"
#include "../../../../game/physics/inc/VerticalSegment.hpp"

#include <gtest/gtest.h>

namespace jp::ut::game::physics
{
   class BodyUpdaterTest : public testing::Test
   {
      protected:
         BodyUpdaterTest()
         {
            mProperties.bounceFactor = 0.5f;
            mProperties.checkCollisionDistance = 600.f;
            mProperties.fallVelocity = 500.f;
            mProperties.slipperyFriction = 200.f;
            mProperties.gravity = math::Vector2<float>(0.f, 800.f);
            mBody.setRect(math::Rect<float>(0.f, 0.f, 24.f, 24.f));
         }

         void SetUp() override {}

         void TearDown() override
         {
            mBody.setPosition(math::Vector2<float>());
            mBody.setVelocity(math::Vector2<float>());
            mSegments.clear();
            mWinds.clear();
         }

         jp::game::physics::BodyUpdater mUpdater;
         jp::game::physics::Body mBody;
         jp::game::physics::Properties mProperties;
         std::vector<std::shared_ptr<jp::game::physics::Segment>> mSegments;
         std::vector<std::shared_ptr<jp::game::physics::Wind>> mWinds;
   };
}