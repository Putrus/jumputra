#include "../inc/QLearning.hpp"

namespace jp::algorithm
{
   QLearning::QLearning(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::QLearning::QLearning - Failed to lock, engine doesn't exist");
      }

      mAgents.push_back(std::make_shared<Wanderer>(mProperties, lockedEngine->characters().back()));
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