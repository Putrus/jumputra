#include "../inc/QLearning.hpp"
#include "../inc/Agent.hpp"

namespace jp::algorithm
{
   QLearning::QLearning(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mGraph(properties), Algorithm(engine, logger, properties)
   {
      *mLogger << "Q-Learning algorithm parameters:" << std::endl;
      *mLogger << "agents = " << properties.qLearning.agents << std::endl;
      *mLogger << "discountFactor = " << properties.qLearning.discountFactor << std::endl;
      *mLogger << "epsilon = " << properties.qLearning.epsilon << std::endl;
      *mLogger << "learningRate = " << properties.qLearning.learningRate << std::endl;
      *mLogger << "randomJumpChance = " << properties.qLearning.randomJumpChance << std::endl;
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::QLearning::QLearning - Failed to lock, engine doesn't exist");
      }

      math::Rect<float> startRect = lockedEngine->characters().back()->getRect();
      lockedEngine->removeAllCharacters();
      for (size_t i = 0; i < properties.qLearning.agents; ++i)
      {
         lockedEngine->addCharacter(startRect);
         mAgents.push_back(std::make_shared<Agent>(mProperties, lockedEngine->characters().back(), mGraph));
      }
   }

   std::string QLearning::getName() const
   {
      return "QLearning";
   }

   void QLearning::update(float dt)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::QLearning::update - Failed to check win, engine doesn't exist");
      }

      if (lockedEngine->getWinner())
      {
         std::vector<std::shared_ptr<logic::Segment>> visitedHorizontalSegments = lockedEngine->getWinner()->getVisitedHorizontalSegments();
         if (visitedHorizontalSegments.empty())
         {
            throw std::runtime_error("jp::algorithm::QLearning::update - Failed to get winner visited horizontal segments, segments are empty");
         }

         std::shared_ptr<logic::Segment> startSegment = visitedHorizontalSegments.front();
         std::shared_ptr<logic::Segment> endSegment = visitedHorizontalSegments.back();
         mMoves = mGraph.getShortestMovesPath(startSegment, endSegment);
      }

      for (auto& agent : mAgents)
      {
         agent->update(dt);
      }
   }
}