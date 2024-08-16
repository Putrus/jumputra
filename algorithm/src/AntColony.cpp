#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      math::Rect<float> startRect = engine->getCharacters().at(0)->getRect();
      mEngine->removeAllCharacters();
      for (int i = 0; i < 200; ++i)
      {
         mEngine->addCharacter(startRect);
         mAnts.push_back(Ant(mPheromones, mEngine->characters().at(i)));
      }
   }

   void AntColony::update(float dt)
   {
      for (auto& pheromones : mPheromones)
      {
         for (auto& pheromone : pheromones.second)
         {
            pheromone.evaporate(dt);
         }

         pheromones.second.erase(std::remove_if(pheromones.second.begin(), pheromones.second.end(),
            [](const auto& element)
            {
               return element.getIntensity() < 0.f;
            }), pheromones.second.end());
      }

      for (auto& ant : mAnts)
      {
         ant.update(dt);
      }
   }
}