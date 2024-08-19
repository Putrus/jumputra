#include "../inc/DecisionTree.hpp"

namespace jp::algorithm
{
   DecisionTree::DecisionTree(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      logic::Character startCharacter = *engine->getCharacters().front();
      engine->removeAllCharacters();
      mNode = std::make_shared<DecisionNode>(nullptr, Move(), mVisitedSegments, startCharacter, engine, properties);
   }

   void DecisionTree::update(float dt)
   {
      mNode->update(dt);
   }
}