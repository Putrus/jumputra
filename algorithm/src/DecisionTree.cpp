#include "../inc/DecisionTree.hpp"

namespace jp::algorithm
{
   DecisionTree::DecisionTree(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties)
   {
      *mLogger << "Decision Tree algorithm parameters:" << std::endl;
      *mLogger << "jumps = " << properties.decisionTree.jumps << std::endl;
      *mLogger << "jumpValue = " << properties.decisionTree.jumpValue << std::endl;
      *mLogger << "runValue = " << properties.decisionTree.runValue << std::endl;

      logic::Character startCharacter = *engine->getCharacters().front();
      engine->removeAllCharacters();
      mNode = std::make_shared<DecisionNode>(nullptr, Move(), mVisitedSegments, mMoves, startCharacter, engine, logger, properties);
   }

   std::string DecisionTree::getName() const
   {
      return "DecisionTree";
   }

   void DecisionTree::update(float dt)
   {
      mNode->update(dt);
   }
}