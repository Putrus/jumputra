#include "../../../logic/inc/Goal.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(GoalTest, CheckWinTrue)
   {
      Goal goal(math::Rect<float>(1.5f, 1.5f, 24.5f, 24.5f));

      EXPECT_TRUE(goal.checkWin(math::Rect<float>(3.5f, 3.5f, 10.5f, 10.5f)));
   }

   TEST(GoalTest, CheckWinFalse)
   {
      Goal goal(math::Rect<float>(1.5f, 1.5f, 24.5f, 24.5f));

      EXPECT_FALSE(goal.checkWin(math::Rect<float>(26.5f, 26.5f, 10.5f, 10.5f)));
   }

   TEST(GoalTest, ConstructorJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.5,
               "top": 2.5,
               "width": 4.5,
               "height": 5.5
            }
         }
         )");

      ASSERT_NO_THROW(Goal goal(json));
   }

   TEST(GoalTest, ConstructorJsonWrongJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "fdect": {
               "left": 1.5,
               "top": 2.5,
               "width": 4.5,
               "height": 5.5
            }
         }
         )");

      ASSERT_ANY_THROW(Goal goal(json));
   }

   TEST(GoalTest, ToJson)
   {
      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "rect": {
               "left": 1.5,
               "top": 2.5,
               "width": 4.5,
               "height": 5.5
            }
         }
         )");

      Goal goal(math::Rect<float>(1.5f, 2.5f, 4.5f, 5.5f));
      nlohmann::json actualJson = goal.toJson();

      EXPECT_EQ(expectedJson, actualJson);
   }
}