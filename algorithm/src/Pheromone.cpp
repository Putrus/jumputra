#include "../inc/Pheromone.hpp"

namespace jp::algorithm
{
   Pheromone::Pheromone(const math::Vector2<float>& position, const Move& move, float intensity, float time)
      : EdgeMove(position, move, intensity, time) {}
}