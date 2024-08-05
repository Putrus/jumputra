#pragma once

#include "Move.hpp"

#include "../../logic/inc/Engine.hpp"

namespace jp::agents
{
   enum class AgentName : int
   {
      Greedy = 0,
      Human,
      Sequence
   };

   std::ostream& operator<<(std::ostream& os, AgentName name);

   class Agent : public logic::Updatable
   {
   public:
      Agent(const std::shared_ptr<logic::Engine>& engine);

      void saveMoves(const std::string &filename) const;

   protected:
      std::shared_ptr<logic::Engine> mEngine;
      std::vector<Move> mMoves;
   };
}