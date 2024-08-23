#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      math::Rect<float> startRect = engine->getCharacters().front()->getRect();
      clearAnts();
      for (int i = 0; i < mProperties.antColony.ants; ++i)
      {
         addAnt(startRect);
      }
   }

   void AntColony::update(float dt)
   {
      for (auto& pheromone : mPheromones)
      {
         pheromone->evaporate(dt);
      }

      mPheromones.erase(std::remove_if(mPheromones.begin(), mPheromones.end(),
         [](const auto& pheromone)
         {
            return pheromone->getIntensity() < 0.f;
         }), mPheromones.end());

      float bestY = std::numeric_limits<float>::max();
      for (auto& ant : mAnts)
      {
         ant->update(dt);
         if (ant->getPosition().y < bestY)
         {
            bestY = ant->getPosition().y;
         }
      }

      if (mPheromonesLastSize != mPheromones.size())
      {
         std::cout << mPheromones.size() << " pos: " << bestY << std::endl;
      }

      mPheromonesLastSize = mPheromones.size();
   }

   void AntColony::addAnt(const math::Rect<float>& rect)
   {
      mEngine->addCharacter(rect);
      mAnts.push_back(std::make_shared<Ant>(mPheromones, mProperties, mEngine->characters().back()));
   }

   void AntColony::clearAnts()
   {
      clearBots();
   }
}