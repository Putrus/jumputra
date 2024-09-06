#include "../inc/DecisionTree.hpp"

namespace jp::algorithm
{
   DecisionTree::DecisionTree(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties)
   {
      logic::Character startCharacter = *engine->getCharacters().front();
      engine->removeAllCharacters();
      mNode = std::make_shared<DecisionNode>(nullptr, Move(), mVisitedSegments, startCharacter, engine, logger, properties);
   }

   void DecisionTree::update(float dt)
   {
      mNode->update(dt);
   }
}