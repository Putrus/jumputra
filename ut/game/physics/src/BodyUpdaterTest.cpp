#include "../inc/BodyUpdaterTest.hpp"

namespace jp::ut::game::physics
{
   using namespace jp::game::physics;

   TEST_F(BodyUpdaterTest, SimpleFlying)
   {      
      mBody.setPosition(math::Vector2<float>(-100.f, -100.f));
      mUpdater.update(0.1f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(-100.f, -96.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(0.f, 80.f), mBody.getVelocity());
      EXPECT_EQ(BodyState::Flying, mBody.getState());
   }

   TEST_F(BodyUpdaterTest, SimpleFalling)
   {      
      mBody.setPosition(math::Vector2<float>(-100.f, -100.f));
      mUpdater.update(1.f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(-100.f, 150.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(0.f, mProperties.fallVelocity), mBody.getVelocity());
      EXPECT_EQ(BodyState::Falling, mBody.getState());
   }

   TEST_F(BodyUpdaterTest, LeftBounceVerticalSegment)
   {      
      mBody.setPosition(math::Vector2<float>(60.f, 100.f));
      mBody.setVelocityX(-15.f);
      mBody.setVelocityY(-400.f);

      mSegments.push_back(std::make_shared<VerticalSegment>(50.f, 0.f, 50.f, 1000.f, SegmentSurface::Ordinary));

      mUpdater.update(1.f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(50, 100.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(7.5f, 400.f), mBody.getVelocity()); 
      EXPECT_EQ(BodyState::Flying, mBody.getState());
   }

   TEST_F(BodyUpdaterTest, RightBounceVerticalSegment)
   {      
      mBody.setPosition(math::Vector2<float>(20.f, 100.f));
      mBody.setVelocityX(20.f);
      mBody.setVelocityY(-400.f);

      mSegments.push_back(std::make_shared<VerticalSegment>(50.f, 0.f, 50.f, 1000.f, SegmentSurface::Ordinary));

      mUpdater.update(1.f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(26, 100.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(-10.f, 400.f), mBody.getVelocity()); 
      EXPECT_EQ(BodyState::Flying, mBody.getState());
   }

   TEST_F(BodyUpdaterTest, LeftBounceHorizontalSegment)
   {      
      mBody.setPosition(math::Vector2<float>(1010.f, 90.f));
      mBody.setVelocityX(-15.f);
      mBody.setVelocityY(-400.f);

      mSegments.push_back(std::make_shared<HorizontalSegment>(100.f, 100.f, 1000.f, 100.f, SegmentSurface::Ordinary));

      mUpdater.update(1.f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(1000, 90.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(7.5f, 400.f), mBody.getVelocity()); 
      EXPECT_EQ(BodyState::Flying, mBody.getState());
   }

   TEST_F(BodyUpdaterTest, RightBounceHorizontalSegment)
   {      
      mBody.setPosition(math::Vector2<float>(70.f, 90.f));
      mBody.setVelocityX(20.f);
      mBody.setVelocityY(-400.f);

      mSegments.push_back(std::make_shared<HorizontalSegment>(100.f, 100.f, 1000.f, 100.f, SegmentSurface::Ordinary));

      mUpdater.update(1.f, mBody, mProperties, mSegments, mWinds);

      EXPECT_EQ(math::Vector2<float>(76.f, 90.f), mBody.getPosition());
      EXPECT_EQ(math::Vector2<float>(-10.f, 400.f), mBody.getVelocity()); 
      EXPECT_EQ(BodyState::Flying, mBody.getState());
   }
}