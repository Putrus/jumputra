#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Ant::Ant(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, AntGraph& antGraph)
      : mGraph(antGraph), Wanderer(properties, character) {}

   void Ant::afterMove(math::Vector2<float>& position)
   {
      Wanderer::afterMove(position);
   }

   void Ant::whileWander(math::Vector2<float>& position)
   {
      Wanderer::whileWander(position);
   }
}