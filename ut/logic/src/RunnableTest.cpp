#include "../../../logic/inc/Runnable.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   class MockRunnable final : public Runnable
   {
   public:
      MockRunnable(const float& secondsPerUpdate) : Runnable(secondsPerUpdate) {}
      
      MOCK_METHOD(void, update, (float dt), (override));
      MOCK_METHOD(void, draw, (), (override));
      
      void event() override
      {
         terminate();
      }
   };

   TEST(RunnableTest, RunOneSecondPerUpdate)
   {
      MockRunnable mockRunnable(1.f);

      EXPECT_CALL(mockRunnable, update(1.f))
         .Times(0);
      
      EXPECT_CALL(mockRunnable, draw())
         .Times(1);

      mockRunnable.run();
   }

   TEST(RunnableTest, RunZeroSecondsPerUpdate)
   {
      MockRunnable mockRunnable(0.f);

      EXPECT_CALL(mockRunnable, update(0.f))
         .Times(1);
      
      EXPECT_CALL(mockRunnable, draw())
         .Times(1);

      mockRunnable.run();
   }

   TEST(RunnableTest, RunMinusOneSecondPerUpdate)
   {
      MockRunnable mockRunnable(-1.f);

      EXPECT_CALL(mockRunnable, update(-1.f))
         .Times(1);
      
      EXPECT_CALL(mockRunnable, draw())
         .Times(1);

      mockRunnable.run();
   }
}