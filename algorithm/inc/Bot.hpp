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
      math::Vector2<float> getPosition() const;
      logic::CharacterDirection getDirection() const;
      const std::vector<std::shared_ptr<logic::Segment>>& getVisitedHorizontalSegments() const;
      std::shared_ptr<logic::Segment> getPreviousVisitedHorizontalSegment() const;
      std::shared_ptr<logic::Segment> getCurrentVisitedHorizontalSegment() const;

      bool finishedMoves() const;

   protected:
      Move getCurrentMove() const;
      Move getFirstMove() const;

      void clearMoves();
      void nextMove();

      logic::CharacterDirection oppositeDirection(logic::CharacterDirection direction) const;

      std::shared_ptr<logic::Character> mCharacter;
      std::vector<std::shared_ptr<logic::Segment>> mVisitedHorizontalSegments;
      bool mFinishedMoves = false;

      struct CurrentMove
      {
         size_t id = 0;
         float value = 0.f;
      } mCurrentMove;

   private:
      void addVisitedHorizontalSegment();
   };
}