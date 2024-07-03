#include "../../../math/inc/Rect.hpp"

#include <gtest/gtest.h>

namespace jp::ut::math
{
   using namespace jp::math;

   TEST(RectFloatTest, DefaultConstructor)
   {
      Rect<float> rect;
      EXPECT_EQ(0.f, rect.left);
      EXPECT_EQ(0.f, rect.top);
      EXPECT_EQ(0.f, rect.width);
      EXPECT_EQ(0.f, rect.height);
   }

   TEST(RectFloatTest, FourArgumentsConstructor)
   {
      Rect<float> rect(1.f, 2.f, 3.f, 4.f);
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloatTest, TwoArgumentsConstructor)
   {
      Rect<float> rect(Vector2<float>(1.f, 2.f), Vector2<float>(3.f, 4.f));
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloatTest, CopyConstructor)
   {
      Rect<float> other(1.f, 2.f, 3.f, 4.f);
      Rect<float> rect(other);
      EXPECT_EQ(1.f, rect.left);
      EXPECT_EQ(2.f, rect.top);
      EXPECT_EQ(3.f, rect.width);
      EXPECT_EQ(4.f, rect.height);
   }

   TEST(RectFloatTest, IntersectsTrue)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(15.f, 15.f, 20.f, 20.f);
      EXPECT_TRUE(rect.intersects(other));
   }

   TEST(RectFloatTest, IntersectsFalse)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(50.f, 50.f, 20.f, 20.f);
      EXPECT_FALSE(rect.intersects(other));
   }

   TEST(RectFloatTest, IntersectsEdge)
   {
      Rect<float> other(10.f, 10.f, 20.f, 20.f);
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_TRUE(rect.intersects(other));
   }

   TEST(RectFloatTest, GetPosition)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 30.f), rect.getPosition());
   }

   TEST(RectFloatTest, GetSize)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(20.f, 20.f), rect.getSize());
   }

   TEST(RectFloatTest, GetLeftTop)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 30.f), rect.getLeftTop());
   }

   TEST(RectFloatTest, GetLeftBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(30.f, 50.f), rect.getLeftBottom());
   }

   TEST(RectFloatTest, GetRightTop)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(50.f, 30.f), rect.getRightTop());
   }

   TEST(RectFloatTest, GetRightBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(50.f, 50.f), rect.getRightBottom());
   }

   TEST(RectFloatTest, GetCenter)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(Vector2<float>(40.f, 40.f), rect.getCenter());
   }

   TEST(RectFloatTest, GetRight)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(50.f, rect.getRight());
   }

   TEST(RectFloatTest, GetBottom)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      EXPECT_EQ(50.f, rect.getBottom());
   }

   TEST(RectFloatTest, SetPositionTwoArguments)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect.setPosition(10.f, 10.f);
      EXPECT_EQ(10.f, rect.left);
      EXPECT_EQ(10.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloatTest, SetPositionOneArgument)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect.setPosition(Vector2<float>(10.f, 10.f));
      EXPECT_EQ(10.f, rect.left);
      EXPECT_EQ(10.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloatTest, PlusOperator)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect = rect + Vector2<float>(10.f, 10.f);
      EXPECT_EQ(40.f, rect.left);
      EXPECT_EQ(40.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloatTest, PlusEqualOperator)
   {
      Rect<float> rect(30.f, 30.f, 20.f, 20.f);
      rect += Vector2<float>(10.f, 10.f);
      EXPECT_EQ(40.f, rect.left);
      EXPECT_EQ(40.f, rect.top);
      EXPECT_EQ(20.f, rect.width);
      EXPECT_EQ(20.f, rect.height);
   }

   TEST(RectFloatTest, StreamExtraction)
   {
      Rect<float> rect(3.4f, 3.4f, 20.f, 20.f);
      std::stringstream ss;
      ss << rect;
      EXPECT_EQ("3.4 3.4 20 20", ss.str());
   }

   TEST(RectFloatTest, EqualEqualOperator)
   {
      Rect<float> rect1(69.f, 69.f, 42.f, 42.f);
      Rect<float> rect2(69.f, 69.f, 42.f, 42.f);
      Rect<float> rect3(690.f, 69.f, 42.f, 42.f);
      EXPECT_TRUE(rect1 == rect2);
      EXPECT_FALSE(rect1 == rect3);
   }

   TEST(RectFloatTest, EqualOperatorJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "left": 1.5,
            "top": 2.5,
            "width": 4.5,
            "height": 5.5
         }
         )");

      Rect<float> rect;
      ASSERT_NO_THROW(rect = json);

      EXPECT_EQ(1.5f, rect.left);
      EXPECT_EQ(2.5f, rect.top);
      EXPECT_EQ(4.5f, rect.width);
      EXPECT_EQ(5.5f, rect.height);
   }

   TEST(RectFloatTest, EqualOperatorWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "left": 1.5,
            "top": 2.5,
            "sidth": 4.5,
            "height": 5.5
         }
         )");

      Rect<float> rect;
      ASSERT_ANY_THROW(rect = json);
   }

   TEST(RectFloatTest, FromJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "left": 1.5,
            "top": 2.5,
            "width": 4.5,
            "height": 5.5
         }
         )");

      Rect<float> rect;
      ASSERT_NO_THROW(rect.fromJson(json));

      EXPECT_EQ(1.5f, rect.left);
      EXPECT_EQ(2.5f, rect.top);
      EXPECT_EQ(4.5f, rect.width);
      EXPECT_EQ(5.5f, rect.height);
   }

   TEST(RectFloatTest, FromJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "left": 1.5,
            "top": 2.5,
            "sidth": 4.5,
            "height": 5.5
         }
         )");

      Rect<float> rect;
      ASSERT_ANY_THROW(rect = json);
   }

   TEST(RectFloatTest, ToJson)
   {
      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "left": 1.5,
            "top": 2.5,
            "width": 4.5,
            "height": 5.5
         }
         )");

      Rect<float> rect(1.5f, 2.5f, 4.5f, 5.5f);
      nlohmann::json actualJson = rect.toJson();

      EXPECT_EQ(expectedJson, actualJson);
   }
}