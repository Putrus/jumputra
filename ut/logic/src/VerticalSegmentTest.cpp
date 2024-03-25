#include "../inc/SegmentTest.hpp"

#include "../../../logic/inc/VerticalSegment.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   typedef SegmentTest VerticalSegmentTest;

   TEST_F(VerticalSegmentTest, InitCorrect)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 0.f, 5.f };
      ASSERT_NO_THROW({ mSegment = new VerticalSegment(a, b); });
      EXPECT_EQ(a, mSegment->a);
      EXPECT_EQ(b, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(VerticalSegmentTest, SwapPoints)
   {
      math::Vector2<float> a = { 0.f, 5.f };
      math::Vector2<float> b = { 0.f, 0.f };
      ASSERT_NO_THROW({ mSegment = new VerticalSegment(a, b); });
      EXPECT_EQ(b, mSegment->a);
      EXPECT_EQ(a, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(VerticalSegmentTest, GetSurfaceSlippery)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 0.f, 5.f };
      ASSERT_NO_THROW({ mSegment = new VerticalSegment(a, b, SegmentSurface::Slippery); });
      EXPECT_EQ(SegmentSurface::Slippery, mSegment->getSurface());
   }

   TEST_F(VerticalSegmentTest, GetSurfaceSticky)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 0.f, 5.f };
      ASSERT_NO_THROW({ mSegment = new VerticalSegment(a, b, SegmentSurface::Sticky); });
      EXPECT_EQ(SegmentSurface::Sticky, mSegment->getSurface());
   }

   TEST_F(VerticalSegmentTest, InitInvalidArgument)
   {
      ASSERT_THROW({ mSegment = new VerticalSegment({ 0.f, 0.f }, { 5.f, 5.f }, SegmentSurface::Ordinary); }, std::invalid_argument);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionSimpleLeft)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 110.f, 150.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 150.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Left, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionSimpleRight)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 50.f, 150.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 150.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Right, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionSimpleTop)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 90.f, 240.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 190.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Top, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionSimpleBottom)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 90.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Bottom, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionDiagonalMovementLeft)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 150.f, 90.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 110.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Left, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionDiagonalMovementRight)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 50.f, 90.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 110.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Right, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionDiagonalMovementTop)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 150.f, 210.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 110.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Top, collision);
   }

   TEST_F(VerticalSegmentTest, CheckCollisionDiagonalMovementBottom)
   {
      ASSERT_NO_THROW({ mSegment = new VerticalSegment({ 100.f, 100.f }, { 100.f, 200.f }, SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 150.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 110.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Bottom, collision);
   }
}