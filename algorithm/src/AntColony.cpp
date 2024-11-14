#include "../inc/AntColony.hpp"

namespace jp::algorithm
{
   AntColony::AntColony(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mGraph(properties), Algorithm(engine, logger, properties)
   {
      *mLogger << "Ant Colony algorithm parameters:" << std::endl;
      *mLogger << "ants = " << properties.antColony.ants << std::endl;
      *mLogger << "evaporationRate = " << properties.antColony.evaporationRate << std::endl;
      *mLogger << "maxIntensity = " << properties.antColony.maxIntensity << std::endl;
      *mLogger << "minIntensity = " << properties.antColony.minIntensity << std::endl;
      *mLogger << "randomJumpChance = " << properties.antColony.randomJumpChance << std::endl;

      math::Rect<float> startRect = engine->getCharacters().front()->getRect();
      clearAnts();
      for (int i = 0; i < mProperties.antColony.ants; ++i)
      {
         addAnt(startRect);
      }

      //to remove, very ugly hardcoded code for babiac world todo
      mStartSegment = engine->getSegmentByPosition(math::Vector2<float>(127, 15448));
      mEndSegment = engine->getSegmentByPosition(math::Vector2<float>(152, 13648));
   }

   std::string AntColony::getName() const
   {
      return "AntColony";
   }

   void AntColony::update(float dt)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::AntColony::update - Failed to check win, engine doesn't exist");
      }

      if (lockedEngine->getWinner())
      {
         mMoves = mGraph.getShortestMovesPath(mStartSegment, mEndSegment);
      }

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
      mAnts.push_back(std::make_shared<Ant>(mProperties, lockedEngine->characters().back(), mGraph, *mLogger));
   }

   void AntColony::clearAnts()
   {
      clearBots();
   }
}