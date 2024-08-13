#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

namespace jp::algorithm
{
   class Genetic final : public Algorithm
   {
   public:
      Genetic(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      void initializePopulation();
      void createPopulation(const std::pair<size_t, size_t>& parents);
      std::pair<size_t, size_t> selectParents() const;
      std::vector<Move> crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const;
      void addRandomMoves(std::vector<Move>& moves) const;
      void changeRandomMoves(std::vector<Move>& moves) const;
      void removeRandomMoves(std::vector<Move>& moves) const;
      void mutate(std::vector<Move>& moves) const;
      void adjustMutationRate(float fitness);

      bool shouldBeMutated() const;

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
      size_t mGeneration = 0;
      float mLastBestFitness = std::numeric_limits<float>::max();
      float mMutationRate = 0.1f;
      math::Rect<float> mStartRect = math::Rect<float>();
   };
}