#pragma once

#include "Movable.hpp"

#include "../../logic/inc/Character.hpp"

namespace jp::algorithm
{
   class Bot : public Movable
   {
   public:
      Bot(const std::shared_ptr<logic::Character>& character, const std::vector<Move>& moves = {});

      virtual void update(float dt) override;

      const std::shared_ptr<logic::Character>& getCharacter() const;

      bool finishedMoves() const;

   protected:
      Move getCurrentMove() const;
      Move getLastMove() const;

      void clearMoves();

      logic::CharacterDirection oppositeDirection(logic::CharacterDirection direction) const;

      std::shared_ptr<logic::Character> mCharacter;
      bool mFinishedMoves = false;

   private:
      void nextMove();

      struct CurrentMove
      {
         size_t id = 0;
         float value = 0.f;
      } mCurrentMove;
   };
}