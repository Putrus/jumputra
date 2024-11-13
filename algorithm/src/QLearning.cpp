#include "../inc/QLearning.hpp"
#include "../inc/Agent.hpp"

namespace jp::algorithm
{
   QLearning::QLearning(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mGraph(properties), Algorithm(engine, logger, properties)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::QLearning::QLearning - Failed to lock, engine doesn't exist");
      }

      // math::Rect<float> startRect = engine->getCharacters().front()->getRect();
      // clearBots();
      // for (int i = 0; i < 100; ++i)
      // {
      //    lockedEngine->addCharacter(startRect);
      //    mAgents.push_back(std::make_shared<Agent>(mProperties, lockedEngine->characters().back(), mGraph));
      // }
      // std::cout << mAgents.size() << std::endl;

      mAgents.push_back(std::make_shared<Agent>(mProperties, lockedEngine->characters().back(), mGraph));
   }

   std::string QLearning::getName() const
   {
      return "QLearning";
   }

   void QLearning::update(float dt)
   {
      for (auto& agent : mAgents)
      {
         agent->update(dt);
      }
   }
}