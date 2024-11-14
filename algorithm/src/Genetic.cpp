#include "../inc/Genetic.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Genetic::Genetic(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mStartRect(engine->getCharacters().at(0)->getRect()), Algorithm(engine, logger, properties)
   {
      *mLogger << "Genetic algorithm parameters:" << std::endl;
      *mLogger << "mutation.change = " << properties.genetic.mutation.change << std::endl;
      *mLogger << "mutation.max = " << properties.genetic.mutation.max << std::endl;
      *mLogger << "population.size = " << properties.genetic.population.size << std::endl;
      *mLogger << "population.elitism = " << properties.genetic.population.elitism << std::endl;
      *mLogger << "tournament = " << properties.genetic.tournament << std::endl;
      *mLogger << "visitedSegmentsImpact = " << properties.genetic.visitedSegmentsImpact << std::endl;
      initializePopulation();
   }

   std::string Genetic::getName() const
   {
      return "Genetic";
   }

   void Genetic::update(float dt)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::Genetic::update - Failed to update, engine doesn't exist");
      }

      for (auto& individual : mPopulation)
      {
         individual->update(dt);
         if (lockedEngine->getWinner() == individual->getCharacter())
         {
            mMoves = individual->getMoves();
            return;
         }
      }

      if (haveIndividualsFinishedMoves())
      {
         std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>> parents = selectParents();
         float newBestFitness = std::min(calculateFitness(parents.first), calculateFitness(parents.second));
         adjustMutationRate(newBestFitness);
         mLastBestFitness = newBestFitness;

         *mLogger << "Generation: " << mGeneration++ << " best fitness: " << newBestFitness <<
            " moves: " << parents.first->getMoves().size() << " mutation: " << mMutationRate << std::endl;
         lockedEngine->resetWinds();
         createPopulation(parents);
      }
   }

   void Genetic::initializePopulation()
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::Genetic::initializePopulation - Failed to initialize population, engine doesn't exist");
      }

      lockedEngine->removeAllCharacters();
      for (size_t i = 0; i < mProperties.genetic.population.size; ++i)
      {
         std::vector<Move> moves;
         for (size_t j = 0; j < 10; ++j)
         {
            moves.push_back(randomMove());
         }
         addIndividual(mStartRect, moves);
      }
   }

   void Genetic::createPopulation(const std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>>& parents)
   {
      std::pair<std::vector<Move>, std::vector<Move>> parentsMoves =
         { parents.first->getMoves(), parents.second->getMoves() };

      clearPopulation();
      size_t elitismSize = static_cast<size_t>(mProperties.genetic.population.size * mProperties.genetic.population.elitism);
      for (size_t i = 0; i < elitismSize; ++i)
      {
         std::vector<Move> moves = crossover(parentsMoves);
         addRandomMoves(moves);
         addIndividual(mStartRect, moves);
      }
      for (size_t i = elitismSize; i < mProperties.genetic.population.size; ++i)
      {
         std::vector<Move> moves = crossover(parentsMoves);
         mutate(moves);
         addIndividual(mStartRect, moves);
      }
   }

   std::shared_ptr<Individual> Genetic::tournament() const
   {
      std::vector<std::shared_ptr<Individual>> candidates;
      size_t tournamentSize = static_cast<size_t>(mProperties.genetic.population.size * mProperties.genetic.tournament);
      for (size_t i = 0; i < tournamentSize; ++i)
      {
         candidates.push_back(mPopulation.at(core::Random::getInt(0, mPopulation.size() - 1)));
      }

      std::shared_ptr<Individual> bestCandidate = candidates.front();
      float bestFitness = calculateFitness(bestCandidate);
      for (const auto& candidate : candidates)
      {
         float fitness = calculateFitness(candidate);
         if (fitness < bestFitness)
         {
            bestCandidate = candidate;
            bestFitness = fitness;
         }
      }

      return bestCandidate;
   }

   std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>> Genetic::selectParents() const
   {
      std::pair<std::shared_ptr<Individual>, std::shared_ptr<Individual>> parents = { tournament(), tournament() };
      while (parents.first == parents.second)
      {
         parents.second = tournament();
      }

      return parents;
   }

   std::vector<Move> Genetic::crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const
   {
      std::vector<Move> moves;
      if (parentsMoves.first.size() < parentsMoves.second.size())
      {
         moves = parentsMoves.second;
      }
      else
      {
         moves = parentsMoves.first;
      }
      size_t crossoverPoint = core::Random::getInt(0, std::min(parentsMoves.first.size(), parentsMoves.second.size()) - 1);
      for (size_t i = 0; i < crossoverPoint; ++i)
      {
         moves.at(i) = parentsMoves.first.at(i);
      }

      return moves;
   }

   void Genetic::addRandomMoves(std::vector<Move>& moves) const
   {
      int randomMoves = core::Random::getInt(1, 5);
      for (int i = 0; i < randomMoves; ++i)
      {
         moves.push_back(randomMove());
      }
   }

   void Genetic::changeRandomMoves(std::vector<Move>& moves) const
   {
      for (auto& move : moves)
      {
         if (!shouldBeMutated())
         {
            continue;
         }

         move = randomMove();
      }
   }

   void Genetic::removeRandomMoves(std::vector<Move>& moves) const
   {
      int randomRemoves = core::Random::getInt(1, 3);
      for (int i = 0; i < randomRemoves && !moves.empty(); ++i)
      {
         size_t id = core::Random::getInt(0, moves.size() - 1);
         moves.erase(moves.begin() + id);
      }
   }

   void Genetic::mutate(std::vector<Move>& moves) const
   {
      if (shouldBeMutated())
      {
         addRandomMoves(moves);
      }
      changeRandomMoves(moves);
      if (shouldBeMutated())
      {
         removeRandomMoves(moves);
      }
   }

   void Genetic::adjustMutationRate(float fitness)
   {
      if (fitness < mLastBestFitness)
      {
         mMutationRate = std::max(mProperties.genetic.mutation.change, mMutationRate - mProperties.genetic.mutation.change);
      }
      else
      {
         mMutationRate = std::min(mProperties.genetic.mutation.max, mMutationRate + mProperties.genetic.mutation.change);
      }
   }

   void Genetic::clearPopulation()
   {
      clearBots();
   }

   void Genetic::addIndividual(const math::Rect<float>& rect, const std::vector<Move>& moves)
   {
      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::Genetic::addIndividual - Failed to add individual, engine doesn't exist");
      }

      lockedEngine->addCharacter(rect);
      mPopulation.push_back(std::make_shared<Individual>(lockedEngine->getCharacters().back(), moves));
   }

   bool Genetic::shouldBeMutated() const
   {
      return core::Random::getFloat(0.f, 1.f) < mMutationRate;
   }

   bool Genetic::haveIndividualsFinishedMoves() const
   {
      return haveBotsFinishedMoves();
   }

   float Genetic::calculateFitness(const std::shared_ptr<Individual>& individual) const
   {
      const logic::Character& finishedCharacter = individual->getFinishedCharacter();
      const logic::Statistics& statistics = finishedCharacter.getStatistics();
      std::set<std::shared_ptr<logic::Segment>> uniqueVisitedSegments(finishedCharacter.getVisitedSegments().begin(),
         finishedCharacter.getVisitedSegments().end());
      return statistics.falls + statistics.jumps + statistics.time + finishedCharacter.getPosition().y +
         finishedCharacter.getVisitedSegments().size() - uniqueVisitedSegments.size() * mProperties.genetic.visitedSegmentsImpact;
   }
}