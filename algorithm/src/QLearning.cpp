#include "../inc/QLearning.hpp"
#include "../inc/Agent.hpp"

namespace jp::algorithm
{
   QLearning::QLearning(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mGraph(properties), Algorithm(engine, logger, properties)
   {
      *mLogger << "Q-Learning algorithm parameters:" << std::endl;
      *mLogger << "discountFactor = " << properties.qLearning.discountFactor << std::endl;
      *mLogger << "epsilon = " << properties.qLearning.epsilon << std::endl;
      *mLogger << "learningRate = " << properties.qLearning.learningRate << std::endl;
      *mLogger << "randomJumpChance = " << properties.qLearning.randomJumpChance << std::endl;
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::QLearning::QLearning - Failed to lock, engine doesn't exist");
      }

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