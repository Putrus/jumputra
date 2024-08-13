#include "../inc/Dummy.hpp"

namespace jp::algorithm
{
   Dummy::Dummy(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties) {}

   void Dummy::update(float dt) {}
}