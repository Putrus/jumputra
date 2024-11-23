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

      void reset(const math::Rect<float>& rect, const std::vector<Move>& moves);

      const std::shared_ptr<logic::Character>& getCharacter() const;
      const std::shared_ptr<logic::Segment>& getCurrentSegment() const;
      math::Vector2<float> getPosition() const;
      math::Vector2<float> getPositionBeforeMoves() const;
      logic::CharacterDirection getDirection() const;
      const logic::Character& getFinishedCharacter() const;
      const std::vector<std::shared_ptr<logic::Segment>>& getVisitedSegments() const;

      bool isSegmentVisited(const std::shared_ptr<logic::Segment>& segment, size_t size) const;
      bool finishedMoves() const;

   protected:
      Move getCurrentMove() const;

      void clearMoves();
      void nextMove();

      std::shared_ptr<logic::Character> mCharacter;
      logic::Character mFinishedCharacter;
      bool mFinishedMoves = false;
      math::Vector2<float> mPositionBeforeMoves = math::Vector2<float>();

      struct CurrentMove
      {
         size_t id = 0;
         float value = 0.f;
      } mCurrentMove;
   };
}