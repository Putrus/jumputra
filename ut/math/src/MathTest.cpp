#include "../../../math/inc/Math.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(MathTest, Vector2FloatAbsoluteValueMinus)
   {
      math::Vector2<float> vec = math::abs(math::Vector2<float>({ -4.2f, -69.69f }));
      EXPECT_EQ(math::Vector2<float>({ 4.2f, 69.69f }), vec);
   }

   TEST(MathTest, Vector2FloatAbsoluteValuePlus)
   {
      math::Vector2<float> vec = math::abs(math::Vector2<float>({ 4.2f, 69.69f }));
      EXPECT_EQ(math::Vector2<float>({ 4.2f, 69.69f }), vec);
   }
}