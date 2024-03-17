#include "../../../math/inc/Math.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(MathTest, Vector2FloatAbsoluteValueMinus)
   {
      Vector2<float> vec = abs(Vector2<float>({ -4.2f, -69.69f }));
      EXPECT_EQ(Vector2<float>({ 4.2f, 69.69f }), vec);
   }

   TEST(MathTest, Vector2FloatAbsoluteValuePlus)
   {
      Vector2<float> vec = abs(Vector2<float>({ 4.2f, 69.69f }));
      EXPECT_EQ(Vector2<float>({ 4.2f, 69.69f }), vec);
   }
}