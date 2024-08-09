#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class Genetic final : public Algorithm
   {
   public:
      Genetic(const std::shared_ptr<logic::Engine>& engine, size_t population = 100);

      void update(float dt) override;

   private:
      void initializePopulation();
      std::pair<size_t, size_t> selectParents() const;
      std::vector<Move> crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const;
      void mutate(std::vector<Move>& moves, float mutationRate);

      struct Individual
      {
         Individual(const std::shared_ptr<logic::Character> logicCharacter)
            : character(*logicCharacter)
         {
            const logic::Statistics &statistics = logicCharacter->getStatistics();
            fitness = statistics.falls + statistics.jumps + statistics.time + logicCharacter->getPosition().y;
         }
         logic::Character character;
         float fitness = 0.f;
      };

      std::map<size_t, Individual> mIndividualsThatFinished;
      std::vector<Bot> mPopulation;
      size_t mPopulationSize;
      float mMutationRate = 0.1f;
      float mLastBestFitness = std::numeric_limits<float>::max();
      math::Rect<float> mStartRect;
      size_t mIteration = 0;
   };
}