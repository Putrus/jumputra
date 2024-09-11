#include "../inc/Human.hpp"

namespace jp::algorithm
{
   Human::Human(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties) {}

   std::string Human::getName() const
   {
      return "Human";
   }

   void Human::update(float dt) {}
}