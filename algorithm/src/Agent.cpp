#include "../inc/Agent.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float COLLISION_THRESHOLD = 1.f;

   Agent::Agent(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, QGraph& graph)
      : mGraph(graph), Wanderer(properties, character) {}

   void Agent::afterMove(math::Vector2<float>& position)
   {
      Wanderer::afterMove(position);
   }

   void Agent::whileWander(math::Vector2<float>& position)
   {
      Wanderer::whileWander(position);
   }
}