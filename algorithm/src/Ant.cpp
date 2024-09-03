#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Ant::Ant(std::vector<std::shared_ptr<Pheromone>>& pheromones,
      const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character)
      : mPheromones(pheromones), mProperties(properties),
      Bot(character, { Move::infiniteRun(logic::CharacterDirection::Right) }) {}

   void Ant::update(float dt)
   {
      Bot::update(dt);

      math::Vector2<float> position = getPosition();
      if (finishedMoves())
      {
         bool find = false;
         if (getVisitedSegments().size() == 1 || getVisitedSegments().back() == mSegmentBeforeJump)
         {
            find = true;
         }

         for (size_t i = 0; i < getVisitedSegments().size() - 1; ++i)
         {
            if (getVisitedSegments().at(i) == getVisitedSegments().back())
            {
               find = true;
               break;
            }
         }

         if (!find)
         {
            auto findPheromone = std::find_if(mPheromones.begin(), mPheromones.end(), [this](const auto& pheromone)
            {
               const math::Vector2<float>& pheromonePosition = pheromone->getPosition();
               return mLastPosition.y == pheromonePosition.y && mLastPosition.x > pheromonePosition.x - 0.5f && mLastPosition.x < pheromonePosition.x + 0.5f;
            });

            if (findPheromone == mPheromones.end())
            {
               float intensity = 50.f;
               if (mLastPosition.y < getPosition().y)
               {
                  intensity = 1.f;
               }

               if (getVisitedSegments().size() < 2)
               {
                  throw std::runtime_error("Ant::update - Failed to add new pheromone, visited segments size is less than 2");
               }

               mPheromones.push_back(std::make_shared<Pheromone>(mLastPosition, getMoves().back(),
                  intensity, getVisitedSegments().at(getVisitedSegments().size() - 2)));
            }
         }

         auto findPheromone = std::find_if(mPheromones.begin(), mPheromones.end(), [this](const auto& pheromone)
            {
               return pheromone->getSegment() == getVisitedSegments().back() && core::Random::getFloat(0.f, 100.f) <= pheromone->getIntensity();
            });

         logic::CharacterDirection runDirection = static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2));

         if (findPheromone != mPheromones.end())
         {
            if ((*findPheromone)->getPosition().x < getPosition().x)
            {
               runDirection = logic::CharacterDirection::Left;
            }
            else
            {
               runDirection = logic::CharacterDirection::Right;
            }
         }
         setMove(Move::infiniteRun(runDirection));
         mLastChangeDirectionPosition = position;
      }
      else if (getCurrentMove().type == MoveType::Run)
      {
         if (mLastPosition == position &&
            mLastChangeDirectionPosition != position)
         {
            setMove(Move::infiniteRun(logic::Character::oppositeDirection(getDirection())));
            mLastChangeDirectionPosition = position;
         }
         mLastPosition = position;

         auto findPheromone = std::find_if(mPheromones.begin(), mPheromones.end(), [position](const auto& pheromone)
            {
               const math::Vector2<float>& pheromonePosition = pheromone->getPosition();
               return position.y == pheromonePosition.y && position.x > pheromonePosition.x - 0.5f && position.x < pheromonePosition.x + 0.5f;
            });

         if (findPheromone != mPheromones.end())
         {
            if (core::Random::getFloat(0.f, 100.f) <= (*findPheromone)->getIntensity())
            {
               setMove((*findPheromone)->getMove());
               (*findPheromone)->increaseIntensity(5.f);
               return;
            }
         }

         if (core::Random::getFloat(0.f, 1.f) <= mProperties.antColony.randomJumpChance)
         {
            if (!getVisitedSegments().empty())
            {
               mSegmentBeforeJump = getVisitedSegments().back();
            }
            setMove(Move::randomSideJump(10.f, mCharacter->getProperties().character.jump.max.y));
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
      mMoves.front() = move;
   }
}