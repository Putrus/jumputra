#include "../../../algorithm/inc/Properties.hpp"

#include <gtest/gtest.h>

namespace jp::ut::algorithm
{
   using namespace jp::algorithm;

   TEST(PropertiesTest, FromJson)
   {
      Properties properties;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "decisionTree": {
               "jumps": 20,
               "jumpValue": 10.0,
               "runValue": 0.075
            },
            "genetic": {
               "population": {
                  "size": 400,
                  "elitism": 150
               },
               "mutation": {
                  "change": 0.25,
                  "max": 0.5
               },
               "tournament": {
                  "size": 200
               }
            },
            "greedy": {
               "bots":  100,
               "epsilon": 0.75
            }
         }
         )");

      ASSERT_NO_THROW(properties.fromJson(json));
      EXPECT_EQ(20, properties.decisionTree.jumps);
      EXPECT_EQ(10.f, properties.decisionTree.jumpValue);
      EXPECT_EQ(0.075f, properties.decisionTree.runValue);

      EXPECT_EQ(400, properties.genetic.population.size);
      EXPECT_EQ(150, properties.genetic.population.elitism);
      EXPECT_EQ(0.25f, properties.genetic.mutation.change);
      EXPECT_EQ(0.5f, properties.genetic.mutation.max);
      EXPECT_EQ(200, properties.genetic.tournament.size);

      EXPECT_EQ(100, properties.greedy.bots);
      EXPECT_EQ(0.75f, properties.greedy.epsilon);
   }

   TEST(PropertiesTest, FromJsonWrongJson)
   {
      Properties properties;

      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "decisionTree": {
               "jumps": 20,
               "jumpValue": 10.0,
               "runValue": 0.075
            },
            "dupenetic": {
               "population": {
                  "size": 400,
                  "elitism": 150
               },
               "mutation": {
                  "change": 0.25,
                  "max": 0.5
               },
               "tournament": {
                  "size": 200
               }
            },
            "greedy": {
               "bots":  100,
               "epsilon": 0.75
            }
         }
         )");

      ASSERT_ANY_THROW(properties.fromJson(json));
   }

   TEST(PropertiesTest, ToJson)
   {
      Properties properties;

      properties.decisionTree.jumps = 10;
      properties.decisionTree.jumpValue = 10.75f;
      properties.decisionTree.runValue = 0.5f;

      properties.genetic.population.size = 400;
      properties.genetic.population.elitism = 150;
      properties.genetic.mutation.change = 0.25f;
      properties.genetic.mutation.max = 0.5f;
      properties.genetic.tournament.size = 200;
      properties.greedy.bots = 100;
      properties.greedy.epsilon = 0.75f;

      nlohmann::json expectedJson = nlohmann::json::parse(R"(
         {
            "decisionTree": {
               "jumps": 10,
               "jumpValue": 10.75,
               "runValue": 0.5
            },
            "genetic": {
               "population": {
                  "size": 400,
                  "elitism": 150
               },
               "mutation": {
                  "change": 0.25,
                  "max": 0.5
               },
               "tournament": {
                  "size": 200
               }
            },
            "greedy": {
               "bots":  100,
               "epsilon": 0.75
            }
         }
         )");

      nlohmann::json actualJson = properties.toJson();

      EXPECT_EQ(expectedJson, actualJson);
   }
}