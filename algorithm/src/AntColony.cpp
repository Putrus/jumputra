#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      math::Rect<float> startRect = engine->getCharacters().at(0)->getRect();
      mEngine->removeAllCharacters();
      for (int i = 0; i < 1; ++i)
      {
         mEngine->addCharacter(startRect);
         mAnts.push_back(Ant(mPheromones, mEngine->characters().at(i)));
      }
   }

   void AntColony::update(float dt)
   {
      for (auto& ant : mAnts)
      {
         ant.update(dt);
      }
   }
}