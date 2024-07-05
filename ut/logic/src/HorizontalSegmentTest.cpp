#include "../inc/SegmentTest.hpp"

#include "../../../logic/inc/HorizontalSegment.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   typedef SegmentTest HorizontalSegmentTest;

   TEST_F(HorizontalSegmentTest, InitCorrect)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 0.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(a, b); });
      EXPECT_EQ(a, mSegment->a);
      EXPECT_EQ(b, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(HorizontalSegmentTest, SwapPoints)
   {
      math::Vector2<float> a = { 5.f, 0.f };
      math::Vector2<float> b = { 0.f, 0.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(a, b); });
      EXPECT_EQ(b, mSegment->a);
      EXPECT_EQ(a, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(HorizontalSegmentTest, GetSurfaceSlippery)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 0.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(a, b, SegmentSurface::Slippery); });
      EXPECT_EQ(SegmentSurface::Slippery, mSegment->getSurface());
   }

   TEST_F(HorizontalSegmentTest, GetSurfaceSticky)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 0.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(a, b, SegmentSurface::Sticky); });
      EXPECT_EQ(SegmentSurface::Sticky, mSegment->getSurface());
   }

   TEST_F(HorizontalSegmentTest, InitInvalidArgument)
   {
      ASSERT_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(0.f, 0.f), math::Vector2<float>(5.f, 5.f)); }, std::invalid_argument);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionSimpleLeft)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 250.f, 90.f, 20.f, 20.f };
      math::Rect<float> newRect = { 190.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Left, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionSimpleRight)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 50.f, 90.f, 20.f, 20.f };
      math::Rect<float> newRect = { 90.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Right, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionSimpleTop)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 150.f, 110.f, 20.f, 20.f };
      math::Rect<float> newRect = { 150.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Top, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionSimpleBottom)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 150.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 150.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Bottom, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionDiagonalMovementLeft)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 210.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 190.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Left, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionDiagonalMovementRight)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 50.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 100.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Right, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionDiagonalMovementTop)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 199.f, 150.f, 20.f, 20.f };
      math::Rect<float> newRect = { 190.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Top, collision);
   }

   TEST_F(HorizontalSegmentTest, CheckCollisionDiagonalMovementBottom)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<HorizontalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 100.f)); });

      math::Rect<float> oldRect = { 199.f, 50.f, 20.f, 20.f };
      math::Rect<float> newRect = { 190.f, 90.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Bottom, collision);
   }
}