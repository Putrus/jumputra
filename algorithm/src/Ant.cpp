#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Ant::Ant(std::map<math::Vector2<float>, std::vector<Pheromone>>& pheromones, const std::shared_ptr<logic::Character>& character)
      : mPheromones(pheromones), Bot(character, { Move::infiniteRun(logic::CharacterDirection::Right) }) {}

   void Ant::update(float dt)
   {
      Bot::update(dt);

      math::Vector2<float> position = getPosition();

      if (finishedMoves())
      {
         if (mPheromones.find(mLastPosition) == mPheromones.end())
         {
            mPheromones.insert({ mLastPosition, std::vector<Pheromone>() });
         }

         if (position < mLastPosition)
         {
            mPheromones.at(mLastPosition).push_back(Pheromone(getFirstMove(), 5000.f));
         }
         else if (position == mLastPosition)
         {
            mPheromones.at(mLastPosition).push_back(Pheromone(getFirstMove(), 2000.f));
         }

         setMove(Move::infiniteRun(getDirection()));
         mLastChangeDirectionPosition = position;
      }
      else
      {
         Move currentMove = getCurrentMove();
         if (currentMove.type == MoveType::Run)
         {
            if (mLastPosition == position &&
               mLastChangeDirectionPosition != position)
            {
               setMove(Move::infiniteRun(logic::Character::oppositeDirection(getDirection())));
               mLastChangeDirectionPosition = position;
            }

            mLastPosition = position;

            if (mPheromones.find(position) != mPheromones.end())
            {
               for (const auto& pheromone : mPheromones.at(position))
               {
                  float random = core::Random::getFloat(0, 10000.f);
                  if (random < pheromone.getIntensity())
                  {
                     setMove(pheromone.getMove());
                     return;
                  }
               }
            }

            int randomNumber = core::Random::getInt(0, 10000);
            if (randomNumber < 100)
            {
               setMove(Move::randomSideJump(1.f, getCharacter()->getProperties().character.jump.max.y));
            }
         }
      }
   }

   void Ant::setMove(const Move& move)
   {
      if (mMoves.empty())
      {
         throw std::runtime_error("Ant::setMove - Failed to set move, moves are empty");
      }
      mFinishedMoves = false;
      mCurrentMove.id = 0;
      mCurrentMove.value = 0.f;
      mMoves.at(0) = move;
   }
}