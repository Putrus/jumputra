#include "../../../math/inc/Segment.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(SegmentFloatTest, DefaultConstructor)
   {
      Segment<float> segment;
      EXPECT_EQ(Vector2<float>(), segment.a);
      EXPECT_EQ(Vector2<float>(), segment.b);
   }

   TEST(SegmentFloatTest, FourArgumentsConstructor)
   {
      Segment<float> segment(10.f, 10.f, 100.f, 100.f);
      EXPECT_EQ(Vector2<float>(10.f, 10.f), segment.a);
      EXPECT_EQ(Vector2<float>(100.f, 100.f), segment.b);
   }

   TEST(SegmentFloatTest, TwoArgumentsConstructor)
   {
      Segment<float> segment(Vector2<float>(10.f, 10.f), Vector2<float>(100.f, 100.f));
      EXPECT_EQ(Vector2<float>(10.f, 10.f), segment.a);
      EXPECT_EQ(Vector2<float>(100.f, 100.f), segment.b);
   }

   TEST(SegmentFloatTest, Diagonal)
   {
      Segment<float> segment(10.f, 10.f, 100.f, 100.f);
      EXPECT_TRUE(segment.isDiagonal());
      EXPECT_FALSE(segment.isHorizontal());
      EXPECT_FALSE(segment.isVertical());
   }

   TEST(SegmentFloatTest, Horizontal)
   {
      Segment<float> segment(10.f, 10.f, 100.f, 10.f);
      EXPECT_FALSE(segment.isDiagonal());
      EXPECT_TRUE(segment.isHorizontal());
      EXPECT_FALSE(segment.isVertical());
   }

   TEST(SegmentFloatTest, Vertical)
   {
      Segment<float> segment(10.f, 10.f, 10.f, 100.f);
      EXPECT_FALSE(segment.isDiagonal());
      EXPECT_FALSE(segment.isHorizontal());
      EXPECT_TRUE(segment.isVertical());
   }

   TEST(SegmentFloatTest, Unknown)
   {
      Segment<float> segment(43.f, 22.f, 1.f, 8.f);
      EXPECT_FALSE(segment.isDiagonal());
      EXPECT_FALSE(segment.isHorizontal());
      EXPECT_FALSE(segment.isVertical());
   }

   TEST(SegmentFloatTest, GetIntercept)
   {
      Segment<float> segment(50.f, 70.f, 200.f, 220.f);
      float intercept = 0.f;
      ASSERT_NO_THROW({ intercept = segment.getIntercept(); });
      EXPECT_EQ(20.f, intercept);
   }

   TEST(SegmentFloatTest, GetSlope)
   {
      Segment<float> segment(10.f, 10.f, 100.f, 100.f);
      float slope = 0.f;
      ASSERT_NO_THROW({ slope = segment.getSlope(); });
      EXPECT_EQ(1.f, slope);
   }

   TEST(SegmentFloatTest, GetSlopeThrowException)
   {
      Segment<float> segment(10.f, 10.f, 10.f, 100.f);
      float slope = 0.f;
      ASSERT_THROW({ slope = segment.getSlope(); }, std::runtime_error);
   }

   TEST(SegmentFloatTest, SwapPoints)
   {
      Segment<float> segment(69.f, 69.f, 42.f, 42.f);
      segment.swapPoints();
      EXPECT_EQ(Vector2<float>(42.f, 42.f), segment.a);
      EXPECT_EQ(Vector2<float>(69.f, 69.f), segment.b);
   }

   TEST(SegmentFloatTest, StreamExtraction)
   {
      Segment<float> segment(6.9f, 6.9f, 42.f, 42.f);
      std::stringstream ss;
      ss << segment;
      EXPECT_EQ("6.9 6.9 -> 42 42", ss.str());
   }

   TEST(SegmentFloatTest, EqualEqualOperator)
   {
      Segment<float> segment1(69.f, 69.f, 42.f, 42.f);
      Segment<float> segment2(69.f, 69.f, 42.f, 42.f);
      Segment<float> segment3(690.f, 69.f, 42.f, 42.f);
      EXPECT_TRUE(segment1 == segment2);
      EXPECT_FALSE(segment1 == segment3);
   }
}