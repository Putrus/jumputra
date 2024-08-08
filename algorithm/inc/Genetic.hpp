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
      float evaluateFitness(const logic::Character& individual) const;
      std::pair<size_t, size_t> selectParents() const;
      std::vector<Move> crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const;
      void mutate(std::vector<Move>& moves, float mutationRate);

      std::map<size_t, logic::Character> mIndividualsThatFinished;
      std::vector<Bot> mPopulation;
      size_t mPopulationSize;

      math::Rect<float> mStartRect;
   };
}