#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mGraph(properties), Algorithm(engine, logger, properties)
   {
      math::Rect<float> startRect = engine->getCharacters().front()->getRect();
      clearAnts();
      for (int i = 0; i < mProperties.antColony.ants; ++i)
      {
         addAnt(startRect);
      }
   }

   std::string AntColony::getName() const
   {
      return "AntColony";
   }

   void AntColony::update(float dt)
   {
      for (auto& ant : mAnts)
      {
         ant->update(dt);
      }

      mGraph.update(dt);
   }

   void AntColony::addAnt(const math::Rect<float>& rect)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::AntColony::addAnt - Failed to add ant, engine doesn't exist");
      }

      lockedEngine->addCharacter(rect);
      mAnts.push_back(std::make_shared<Ant>(mProperties, lockedEngine->characters().back(), mGraph));
   }

   void AntColony::clearAnts()
   {
      clearBots();
   }
}