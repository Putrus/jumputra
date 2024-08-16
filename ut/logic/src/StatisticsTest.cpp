#include "../../../logic/inc/Statistics.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(StatisticsTest, FromJson)
   {
      Statistics statistics;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "jumps": 20,
            "falls": 32,
            "time": 76.5,
            "totalTime": 54.75
         }
         )");

      ASSERT_NO_THROW(statistics.fromJson(json));
      EXPECT_EQ(20, statistics.jumps);
      EXPECT_EQ(32, statistics.falls);
      EXPECT_EQ(76.5f, statistics.time);
      EXPECT_EQ(54.75f, statistics.totalTime);
   }

   TEST(StatisticsTest, FromJsonWrongJson)
   {
      Statistics statistics;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "dumps": 20,
            "falls": 32,
            "time": 76.5
         }
         )");

      ASSERT_ANY_THROW(statistics.fromJson(json));
   }

   TEST(StatisticsTest, ToJson)
   {
      Statistics statistics;

      statistics.jumps = 35;
      statistics.falls = 22;
      statistics.time = 340.25f;
      statistics.totalTime = 23.75f;

      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "jumps": 35,
            "falls": 22,
            "time": 340.25,
            "totalTime": 23.75
         }
         )");

      nlohmann::json actualJson = statistics.toJson();

      EXPECT_EQ(expectedJson, actualJson);
   }
}