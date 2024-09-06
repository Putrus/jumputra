#include "../inc/Dummy.hpp"

namespace jp::algorithm
{
   Dummy::Dummy(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties) {}

   void Dummy::update(float dt) {}
}