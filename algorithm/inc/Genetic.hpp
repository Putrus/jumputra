#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

constexpr float MUTATION_RATE_MAX = 0.05f;
constexpr float MUTATION_RATE_CHANGE = 0.01f;

namespace jp::algorithm
{
   class Genetic final : public Algorithm
   {
   public:
      Genetic(const std::shared_ptr<logic::Engine>& engine, size_t population = 100);

      void update(float dt) override;

   private:
      void initializePopulation();
      void createPopulation(const std::pair<size_t, size_t>& parents);
      std::pair<size_t, size_t> selectParents() const;
      std::vector<Move> crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const;
      void mutate(std::vector<Move>& moves, float mutationRate);
      void adjustMutationRate(float fitness);

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
      size_t mIteration = 0;
      size_t mPopulationSize = 0;
      float mLastBestFitness = std::numeric_limits<float>::max();
      float mMutationRate = MUTATION_RATE_MAX;
      float mNewMovesDist = 0.1f;
      math::Rect<float> mStartRect;
   };
}