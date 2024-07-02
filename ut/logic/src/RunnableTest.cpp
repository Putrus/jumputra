#include "../../../logic/inc/Runnable.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   class MockRunnable final : public jp::logic::Runnable
   {
   public:
      MockRunnable(const float& secondsPerUpdate) : jp::logic::Runnable(secondsPerUpdate) {}

      void terminate()
      {
         Runnable::terminate();
      }

      MOCK_METHOD(void, update, (float dt), (override));
      MOCK_METHOD(void, draw, (), (override));
      MOCK_METHOD(void, event, (), (override));
   };

   TEST(RunnableTest, InitCorrect)
   {
      MockRunnable mockRunnable(1.f);
      EXPECT_CALL(mockRunnable, update(1.f))
        .Times(3);
      
      std::thread t(&Runnable::run, &mockRunnable);
      t.join();
      std::this_thread::sleep_for(std::chrono::milliseconds(3500));
      mockRunnable.terminate();
   }
}