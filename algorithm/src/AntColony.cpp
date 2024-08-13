#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties) {}

   void AntColony::update(float dt) {}
}