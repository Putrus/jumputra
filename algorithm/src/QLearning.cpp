#include "../inc/QLearning.hpp"

namespace jp::algorithm
{
   QLearning::QLearning(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties) {}

   std::string QLearning::getName() const
   {
      return "QLearning";
   }

   void QLearning::update(float dt) {}
}