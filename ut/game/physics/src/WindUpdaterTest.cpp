#include "../inc/WindUpdaterTest.hpp"

namespace jp::ut::game::physics
{
   using namespace jp::game::physics;

   TEST_F(WindUpdaterTest, Update0ToMax)
   {
      auto wind = std::make_shared<Wind>(0.5f, math::Vector2<float>(100.f, 100.f),
         math::Rect<float>(0.f, 0.f, 480.f, 360.f), math::Vector2<float>(1.f, 1.f));
      
      float dt = 1.f;
      for(int i = 0; i < 100; ++i)
      {
         mUpdater.update(dt, *wind);
      }

      EXPECT_EQ(0.5f, wind->getImpact());
      EXPECT_EQ(math::Vector2<float>(-100.f, -100.f), wind->getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 480.f, 360.f), wind->getRect());
      EXPECT_EQ(math::Vector2<float>(-1.f, -1.f), wind->getAcceleration()); 
      EXPECT_EQ(math::Vector2<float>(100.f, 100.f), wind->getVelocity());
   }

   TEST_F(WindUpdaterTest, Update0ToMaxAndBack)
   {
      auto wind = std::make_shared<Wind>(0.5f, math::Vector2<float>(100.f, 100.f),
         math::Rect<float>(0.f, 0.f, 480.f, 360.f), math::Vector2<float>(1.f, 1.f));
      
      float dt = 1.f;
      for(int i = 0; i < 200; ++i)
      {
         mUpdater.update(dt, *wind);
      }

      EXPECT_EQ(0.5f, wind->getImpact());
      EXPECT_EQ(math::Vector2<float>(-100.f, -100.f), wind->getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 480.f, 360.f), wind->getRect());
      EXPECT_EQ(math::Vector2<float>(-1.f, -1.f), wind->getAcceleration());
      EXPECT_EQ(math::Vector2<float>(0.f, 0.f), wind->getVelocity());
   }

   TEST_F(WindUpdaterTest, UpdateSeveralLoops)
   {
      auto wind = std::make_shared<Wind>(0.5f, math::Vector2<float>(360.f, -360.f),
         math::Rect<float>(0.f, 0.f, 480.f, 360.f), math::Vector2<float>(3.6f, -3.6f));
      
      float dt = 10.f;
      for(int i = 0; i < 111; ++i)
      {
         mUpdater.update(dt, *wind);
      }

      EXPECT_EQ(0.5f, wind->getImpact());
      EXPECT_EQ(math::Vector2<float>(360.f, -360.f), wind->getMaxVelocity());
      EXPECT_EQ(math::Rect<float>(0.f, 0.f, 480.f, 360.f), wind->getRect());
      EXPECT_EQ(math::Vector2<float>(3.6f, -3.6f), wind->getAcceleration());
      EXPECT_EQ(math::Vector2<float>(-324.f, 324.f), wind->getVelocity());
   }
}