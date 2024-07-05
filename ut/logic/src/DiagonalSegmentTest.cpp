#include "../inc/SegmentTest.hpp"

#include "../../../logic/inc/DiagonalSegment.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   typedef SegmentTest DiagonalSegmentTest;

   TEST_F(DiagonalSegmentTest, InitCorrect)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 5.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(a, b, SegmentSurface::Ordinary); });
      EXPECT_EQ(a, mSegment->a);
      EXPECT_EQ(b, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(DiagonalSegmentTest, SwapPoints)
   {
      math::Vector2<float> a = { 5.f, 5.f };
      math::Vector2<float> b = { 0.f, 0.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(a, b, SegmentSurface::Ordinary); });
      EXPECT_EQ(b, mSegment->a);
      EXPECT_EQ(a, mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST_F(DiagonalSegmentTest, GetSurfaceSlippery)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 5.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(a, b, SegmentSurface::Slippery); });
      EXPECT_EQ(a, mSegment->a);
      EXPECT_EQ(b, mSegment->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegment->getSurface());
   }

   TEST_F(DiagonalSegmentTest, GetSurfaceSticky)
   {
      math::Vector2<float> a = { 0.f, 0.f };
      math::Vector2<float> b = { 5.f, 5.f };
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(a, b, SegmentSurface::Sticky); });
      EXPECT_EQ(a, mSegment->a);
      EXPECT_EQ(b, mSegment->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegment->getSurface());
   }

   TEST_F(DiagonalSegmentTest, InitInvalidArgument)
   {
      ASSERT_THROW({ mSegment = std::make_shared<DiagonalSegment>(math::Vector2<float>(0.f, 0.f), math::Vector2<float>(0.f, 5.f), SegmentSurface::Ordinary); }, std::invalid_argument);
   }

   TEST_F(DiagonalSegmentTest, CheckCollisionSimpleLeft)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 200.f), SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 210.f, 195.f, 20.f, 20.f };
      math::Rect<float> newRect = { 199.f, 195.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Left, collision);
   }

   TEST_F(DiagonalSegmentTest, CheckCollisionSimpleRight)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 0.f), SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 50.f, 97.f, 20.f, 20.f };
      math::Rect<float> newRect = { 81.f, 97.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Right, collision);
   }

   TEST_F(DiagonalSegmentTest, CheckCollisionSimpleAttic)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 0.f), SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 150.f, 110.f, 20.f, 20.f };
      math::Rect<float> newRect = { 150.f, 45.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Attic, collision);
   }

   TEST_F(DiagonalSegmentTest, CheckCollisionSimpleRoof)
   {
      ASSERT_NO_THROW({ mSegment = std::make_shared<DiagonalSegment>(math::Vector2<float>(100.f, 100.f), math::Vector2<float>(200.f, 200.f), SegmentSurface::Ordinary); });

      math::Rect<float> oldRect = { 150.f, 90.f, 20.f, 20.f };
      math::Rect<float> newRect = { 150.f, 145.f, 20.f, 20.f };
      SegmentCollision collision = mSegment->checkCollision(oldRect, newRect);
      EXPECT_EQ(SegmentCollision::Roof, collision);
   }
}