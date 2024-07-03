#include "../../../math/inc/Math.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(MathTest, Vector2FloatAbsoluteValueMinus)
   {
      Vector2<float> vec = abs(Vector2<float>(-4.2f, -69.69f));
      EXPECT_EQ(Vector2<float>(4.2f, 69.69f), vec);
   }

   TEST(MathTest, Vector2FloatAbsoluteValuePlus)
   {
      Vector2<float> vec = abs(Vector2<float>(4.2f, 69.69f));
      EXPECT_EQ(Vector2<float>(4.2f, 69.69f), vec);
   }

   TEST(MathTest, Vector2FloatAbsoluteValuePlusMinus)
   {
      Vector2<float> vec = abs(Vector2<float>(4.2f, -69.69f));
      EXPECT_EQ(Vector2<float>(4.2f, 69.69f), vec);
   }

   TEST(MathTest, Vector2FloatCrossProductZero)
   {
      Vector2<float> a = Vector2<float>(3.f, 6.f);
      Vector2<float> b = Vector2<float>(2.f, 4.f);
      EXPECT_EQ(0.f, crossProduct(a, b));
   }

   TEST(MathTest, Vector2FloatCrossProductSimple)
   {
      Vector2<float> a = Vector2<float>(3.f, 6.f);
      Vector2<float> b = Vector2<float>(2.f, 5.f);
      EXPECT_EQ(3.f, crossProduct(a, b));
   }

   TEST(MathTest, FloatSignPlus)
   {
      EXPECT_EQ(1.f, sign(10.f));
   }

   TEST(MathTest, FloatSignMinus)
   {
      EXPECT_EQ(-1.f, sign(-15.f));
   }

   TEST(MathTest, FloatSignZero)
   {
      EXPECT_EQ(0.f, sign(0.f));
   }
}