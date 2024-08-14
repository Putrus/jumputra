#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Ant::Ant(std::map<math::Vector2<float>, std::vector<Pheromone>>& pheromones, const std::shared_ptr<logic::Character>& character)
      : mPheromones(pheromones), Bot(character, { Move(MoveType::Run, logic::CharacterDirection::Right, 2.f) }) {}

   void Ant::update(float dt)
   {
      Bot::update(dt);

      if (finishedMoves())
      {
         Move lastMove = getLastMove();
         float intensity = 0.f;
         if (getCharacter()->getPosition().y < mLastPosition.y)
         {
            intensity = 500.f;
         }
         else if (getCharacter()->getPosition().y == mLastPosition.y)
         {
            intensity = 250.f;
         }
         else
         {
            intensity = 100.f;
         }

         if (mPheromones.find(mLastPosition) == mPheromones.end())
         {
            mPheromones[mLastPosition] = std::vector<Pheromone>();
         }
         mPheromones.at(mLastPosition).push_back(Pheromone(lastMove, intensity));
      }

      Move currentMove = getCurrentMove();
      if (currentMove.type == MoveType::Run)
      {
         if (mLastPosition == getCharacter()->getPosition() &&
            mLastChangeDirectionPosition != getCharacter()->getPosition())
         {
            std::cout << "lastpos: " << mLastPosition << " lastchangedirpos: " << mLastChangeDirectionPosition << " pos: " << getCharacter()->getPosition() << std::endl;
            clearMoves();
            mMoves.push_back(Move(MoveType::Run, oppositeDirection(getCharacter()->getDirection()), std::numeric_limits<float>::max()));
            mLastChangeDirectionPosition = getCharacter()->getPosition();
         }
         mLastPosition = getCharacter()->getPosition();

         if (core::Random::getInt(0, 1000) <= 1)
         {
            clearMoves();
            mMoves.push_back(Move::randomJump(1.f, 500.f));
         }
      }
   }
}