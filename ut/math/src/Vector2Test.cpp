#include "../../../math/inc/Vector2.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(Vector2FloatTest, DefaultConstructor)
   {
      Vector2<float> v;
      EXPECT_EQ(0.f, v.x);
      EXPECT_EQ(0.f, v.y);
   }

   TEST(Vector2FloatTest, OneArgumentConstructor)
   {
      Vector2<float> v(10.f);
      EXPECT_EQ(10.f, v.x);
      EXPECT_EQ(10.f, v.y);
   }

   TEST(Vector2FloatTest, TwoArgumentsConstructor)
   {
      Vector2<float> v(4.4f, 5.5f);
      EXPECT_EQ(4.4f, v.x);
      EXPECT_EQ(5.5f, v.y);
   }

   TEST(Vector2FloatTest, CopyConstructor)
   {
      Vector2<float> other(-5.5f, -6.6f);
      Vector2<float> v(other);
      EXPECT_EQ(other.x, v.x);
      EXPECT_EQ(other.y, v.y);
   }

   TEST(Vector2FloatTest, CrossProduct)
   {
      Vector2<float> v1(-3.5f, 2.5f);
      Vector2<float> v2(2.5, -3.5f);
      EXPECT_EQ(6.f, v1.cross(v2));
   }

   TEST(Vector2FloatTest, AddingTwoVectors)
   {
      Vector2<float> v1(-3.5f, 2.5f);
      Vector2<float> v2(2.5, -3.5f);
      Vector2<float> sum = v1 + v2;
      EXPECT_EQ(Vector2<float>(-1.f, -1.f), sum);
   }

   TEST(Vector2FloatTest, DifferenceOfTwoVectors)
   {
      Vector2<float> v1(-3.5f, 2.5f);
      Vector2<float> v2(2.5, -3.5f);
      Vector2<float> diff = v1 - v2;
      EXPECT_EQ(Vector2<float>(-6.f, 6.f), diff);
   }

   TEST(Vector2FloatTest, MultiplyingVectorByNumber)
   {
      Vector2<float> v(-3.5f, 2.5f);
      float num = 2.f;
      Vector2<float> product = v * num;
      EXPECT_EQ(Vector2<float>(-7.f, 5.f), product);
   }

   TEST(Vector2FloatTest, DividingVectorByNumber)
   {
      Vector2<float> v(-3.5f, 2.5f);
      float num = 2.f;
      Vector2<float> quotient = v / num;
      EXPECT_EQ(Vector2<float>(-1.75f, 1.25f), quotient);
   }

   TEST(Vector2FloatTest, PlusEqualOperator)
   {
      Vector2<float> v(-3.5f, 2.5f);
      Vector2<float> other(13.5f, 17.5f);
      v += other;
      EXPECT_EQ(Vector2<float>(10.f, 20.f), v);
   }

   TEST(Vector2FloatTest, MinusEqualOperator)
   {
      Vector2<float> v(-3.5f, 2.5f);
      Vector2<float> other(13.5f, 17.5f);
      v -= other;
      EXPECT_EQ(Vector2<float>(-17.f, -15.f), v);
   }

   TEST(Vector2FloatTest, MultiplyEqualOperator)
   {
      Vector2<float> v(-3.5f, 2.5f);
      float num = 3.f;
      v *= num;
      EXPECT_EQ(Vector2<float>(-10.5f, 7.5f), v);
   }

   TEST(Vector2FloatTest, StreamInsertion)
   {
      Vector2<float> v;
      std::stringstream ss("10.0 15.0");
      ss >> v;
      EXPECT_EQ(Vector2<float>(10.f, 15.f), v);
   }

   TEST(Vector2FloatTest, StreamExtraction)
   {
      Vector2<float> v(5.5f, 6.6f);
      std::stringstream ss;
      ss << v;
      EXPECT_EQ("5.5 6.6", ss.str());
   }

   TEST(Vector2FloatTest, EqualEqualOperator)
   {
      Vector2<float> v1(5.5f, 6.6f);
      Vector2<float> v2(5.5f, 6.6f);
      Vector2<float> v3(12.f, 15.f);
      EXPECT_TRUE(v1 == v2);
      EXPECT_FALSE(v1 == v3);
   }

   TEST(Vector2FloatTest, NotEqualOperator)
   {
      Vector2<float> v1(5.5f, 6.6f);
      Vector2<float> v2(5.5f, 6.6f);
      Vector2<float> v3(12.f, 15.f);
      EXPECT_FALSE(v1 != v2);
      EXPECT_TRUE(v1 != v3);
   }
}