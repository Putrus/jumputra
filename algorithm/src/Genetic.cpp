#include "../inc/Genetic.hpp"

namespace jp::algorithm
{
   Genetic::Genetic(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : mStartRect(engine->getCharacters().at(0)->getRect()), Algorithm(engine, properties)
   {
      initializePopulation();
   }

   void Genetic::update(float dt)
   {
      for (size_t i = 0; i < mPopulation.size(); ++i)
      {
         mPopulation.at(i).update(dt);
         if (mIndividualsThatFinished.find(i) == mIndividualsThatFinished.end() && mPopulation.at(i).finishedMoves())
         {
            mIndividualsThatFinished.insert({ i, Individual(mPopulation.at(i).getCharacter()) });
         }
      }

      if (mIndividualsThatFinished.size() == mProperties.genetic.population.size)
      {
         std::pair<size_t, size_t> parents = selectParents();
         float newBestFitness = std::min(mIndividualsThatFinished.at(parents.first).fitness, mIndividualsThatFinished.at(parents.second).fitness);
         adjustMutationRate(newBestFitness);
         mLastBestFitness = newBestFitness;

         std::cout << "Generation: " << mGeneration++ <<
            " first: " << mIndividualsThatFinished.at(parents.first).fitness << " moves: " << mPopulation.at(parents.first).getMoves().size() <<
            " second: " << mIndividualsThatFinished.at(parents.second).fitness << " moves: " << mPopulation.at(parents.second).getMoves().size() <<
            " mutation: " << mMutationRate << std::endl;

         createPopulation(parents);
      }
   }

   void Genetic::initializePopulation()
   {
      mEngine->removeAllCharacters();
      for (size_t i = 0; i < mProperties.genetic.population.size; ++i)
      {
         mEngine->addCharacter(mStartRect);
         std::vector<Move> moves;
         for (size_t j = 0; j < 10; ++j)
         {
            moves.push_back(randomMove());
         }
         mPopulation.push_back(Bot(mEngine->characters().at(i), moves));
      }
   }

   void Genetic::createPopulation(const std::pair<size_t, size_t>& parents)
   {
      std::pair<std::vector<Move>, std::vector<Move>> parentsMoves =
         { mPopulation.at(parents.first).getMoves(), mPopulation.at(parents.second).getMoves() };
      mIndividualsThatFinished.clear();
      mPopulation.clear();
      mEngine->removeAllCharacters();
      for (size_t i = 0; i < mProperties.genetic.population.elitism; ++i)
      {
         mEngine->addCharacter(mStartRect);
         std::vector<Move> moves = crossover(parentsMoves);
         addRandomMoves(moves);
         mPopulation.push_back(Bot(mEngine->characters().at(i), moves));
      }
      for (size_t i = mProperties.genetic.population.elitism; i < mProperties.genetic.population.size; ++i)
      {
         mEngine->addCharacter(mStartRect);
         std::vector<Move> moves = crossover(parentsMoves);
         mutate(moves);
         mPopulation.push_back(Bot(mEngine->characters().at(i), moves));
      }
   }

   std::pair<size_t, size_t> Genetic::selectParents() const
   {
      struct Candidate
      {
         size_t id;
         float fitness;
      };

      auto tournament = [this](size_t tournamentSize) -> Candidate
      {
         std::vector<size_t> candidates;
         for (size_t i = 0; i < tournamentSize; ++i)
         {
            size_t candidate = randomInt(0, mIndividualsThatFinished.size() - 1);
            candidates.push_back(candidate);
         }

         Candidate bestCandidate;
         bestCandidate.id = candidates.front();
         bestCandidate.fitness = mIndividualsThatFinished.at(bestCandidate.id).fitness;
         for (const auto& candidate : candidates)
         {
            float fitness = mIndividualsThatFinished.at(candidate).fitness;
            if (fitness < bestCandidate.fitness)
            {
               bestCandidate.id = candidate;
               bestCandidate.fitness = fitness;
            }
         }

         return bestCandidate;
      };

      std::pair<Candidate, Candidate> parents = { tournament(mProperties.genetic.tournament.size),
         tournament(mProperties.genetic.tournament.size) };
      while (parents.first.id == parents.second.id)
      {
         parents.second = tournament(mProperties.genetic.tournament.size);
      }

      return { parents.first.id, parents.second.id };
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
      size_t crossoverPoint = randomInt(0, std::min(parentsMoves.first.size(), parentsMoves.second.size()) - 1);
      for (size_t i = 0; i < crossoverPoint; ++i)
      {
         moves.at(i) = parentsMoves.first.at(i);
      }

      return moves;
   }

   void Genetic::addRandomMoves(std::vector<Move>& moves) const
   {
      int randomMoves = randomInt(1, 10);
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
      int randomRemoves = randomInt(1, 5);
      for (int i = 0; i < randomRemoves && !moves.empty(); ++i)
      {
         size_t id = randomInt(0, moves.size() - 1);
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

   bool Genetic::shouldBeMutated() const
   {
      return randomFloat(0.f, 1.f) < mMutationRate;
   }
}