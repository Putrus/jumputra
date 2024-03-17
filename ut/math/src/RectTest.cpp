#include "../../../math/inc/Rect.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(RectFloat, DefaultConstructor)
   {
      Rect<float> rect;
      EXPECT_EQ(0.f, rect.left);
      EXPECT_EQ(0.f, rect.top);
      EXPECT_EQ(0.f, rect.width);
      EXPECT_EQ(0.f, rect.height);
   }

   TEST(RectFloat, FourArgumentsConstructor)
   {
      Rect<float> rect(1.f, 2.f, 3.f, 4.f);
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloat, TwoArgumentsConstructor)
   {
      Rect<float> rect(Vector2<float>(1.f, 2.f), Vector2<float>(3.f, 4.f));
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloat, CopyConstructor)
   {
      Rect<float> other(1.f, 2.f, 3.f, 4.f);
      Rect<float> rect(other);
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloat, IntersectsTrue)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(15.f, 15.f, 20.f, 20.f);
      EXPECT_TRUE(rect.intersects(other));
   }

   TEST(RectFloat, IntersectsFalse)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(50.f, 50.f, 20.f, 20.f);
      EXPECT_FALSE(rect.intersects(other));
   }

   TEST(RectFloat, IntersectsEdge)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_TRUE(rect.intersects(other));
   }

   TEST(RectFloat, GetPosition)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 30.f), rect.getPosition());
   }

   TEST(RectFloat, GetSize)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(20.f, 20.f), rect.getSize());
   }

   TEST(RectFloat, GetLeftTop)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 30.f), rect.getLeftTop());
   }

   TEST(RectFloat, GetLeftBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 50.f), rect.getLeftBottom());
   }

   TEST(RectFloat, GetRightTop)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(50.f, 30.f), rect.getRightTop());
   }

   TEST(RectFloat, GetRightBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(50.f, 50.f), rect.getRightBottom());
   }

   TEST(RectFloat, GetCenter)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(40.f, 40.f), rect.getCenter());
   }

   TEST(RectFloat, GetRight)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(50.f, rect.getRight());
   }

   TEST(RectFloat, GetBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(50.f, rect.getBottom());
   }

   TEST(RectFloat, SetPositionTwoArguments)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect.setPosition(10.f, 10.f);
      EXPECT_EQ(10.f, rect.left);
      EXPECT_EQ(10.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloat, SetPositionOneArgument)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect.setPosition(Vector2<float>(10.f, 10.f));
      EXPECT_EQ(10.f, rect.left);
      EXPECT_EQ(10.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloat, PlusOperator)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect = rect + Vector2<float>(10.f, 10.f);
      EXPECT_EQ(40.f, rect.left);
      EXPECT_EQ(40.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloat, PlusEqualOperator)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect += Vector2<float>(10.f, 10.f);
      EXPECT_EQ(40.f, rect.left);
      EXPECT_EQ(40.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloat, StreamExtraction)
   {
      Rect<float> rect(3.4f, 3.4f, 20.f, 20.f);
      std::stringstream ss;
      ss << rect;
      EXPECT_EQ("3.4 3.4 20 20", ss.str());
   }

   TEST(RectFloat, EqualEqualOperator)
   {
      Rect<float> rect1(69.f, 69.f, 42.f, 42.f);
      Rect<float> rect2(69.f, 69.f, 42.f, 42.f);
      Rect<float> rect3(690.f, 69.f, 42.f, 42.f);
      EXPECT_TRUE(rect1 == rect2);
      EXPECT_FALSE(rect1 == rect3);
   }

}