#include "../inc/Dummy.hpp"

namespace jp::algorithm
{
   Dummy::Dummy(const std::shared_ptr<logic::Engine>& engine) : Algorithm(engine) {}

   void Dummy::update(float dt) {}
}