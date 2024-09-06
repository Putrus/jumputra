#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

#include <set>

namespace jp::algorithm
{
   typedef Bot Individual;

   class Genetic final : public Algorithm
   {
   public:
      Genetic(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      void initializePopulation();
      void createPopulation(const std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>>& parents);
      std::shared_ptr<Individual> tournament() const;
      std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>> selectParents() const;
      std::vector<Move> crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const;
      void addRandomMoves(std::vector<Move>& moves) const;
      void changeRandomMoves(std::vector<Move>& moves) const;
      void removeRandomMoves(std::vector<Move>& moves) const;
      void mutate(std::vector<Move>& moves) const;
      void adjustMutationRate(float fitness);
      void clearPopulation();
      void addIndividual(const math::Rect<float>& rect, const std::vector<Move>& moves);

      bool shouldBeMutated() const;
      bool haveIndividualsFinishedMoves() const;

      float calculateFitness(const std::shared_ptr<Individual>& individual) const;

      size_t mGeneration = 0;
      float mLastBestFitness = std::numeric_limits<float>::max();
      float mMutationRate = 0.1f;
      math::Rect<float> mStartRect = math::Rect<float>();
      std::vector<std::shared_ptr<Individual>>& mPopulation = mBots;
   };
}