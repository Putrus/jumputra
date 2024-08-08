#include "../inc/Genetic.hpp"

namespace jp::algorithm
{
   Genetic::Genetic(const std::shared_ptr<logic::Engine>& engine, size_t population/* = 100*/)
      : mPopulationSize(population), mStartRect(engine->getCharacters().at(0)->getRect()), Algorithm(engine)
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
            mIndividualsThatFinished.insert({ i, logic::Character(*mPopulation.at(i).getCharacter()) });
         }
      }

      if (mIndividualsThatFinished.size() == mPopulationSize)
      {
         std::pair<size_t, size_t> parents = selectParents();
         std::pair<std::vector<Move>, std::vector<Move>> parentsMoves =
            { mPopulation.at(parents.first).getMoves(), mPopulation.at(parents.second).getMoves() };
         mIndividualsThatFinished.clear();
         mPopulation.clear();
         mEngine->removeAllCharacters();
         for (size_t i = 0; i < mPopulationSize; ++i)
         {
            mEngine->addCharacter(mStartRect);
            std::vector<Move> moves = crossover(parentsMoves);
            mutate(moves, 0.1f);
            mPopulation.push_back(Bot(mEngine->characters().at(i), crossover(parentsMoves)));
         }
      }
   }

   void Genetic::initializePopulation()
   {
      mEngine->removeAllCharacters();
      for (int i = 0; i < mPopulationSize; ++i)
      {
         mEngine->addCharacter(mStartRect);
         mPopulation.push_back(Bot(mEngine->characters().at(i), { randomMove(), randomMove(), randomMove() }));
      }
   }

   float Genetic::evaluateFitness(const logic::Character& individual) const
   {
      const logic::Statistics &statistics = individual.getStatistics();
      float fitness = statistics.falls + statistics.jumps + statistics.time + individual.getPosition().y;
      return fitness;
   }

   std::pair<size_t, size_t> Genetic::selectParents() const
   {
      struct Parent
      {
         size_t id;
         float fitness;
      };
      std::pair<Parent, Parent> parents = { { 0, std::numeric_limits<float>::max() }, { 0, std::numeric_limits<float>::max() }};
      for (const auto& individual : mIndividualsThatFinished)
      {
         float fitness = evaluateFitness(individual.second);
         if (fitness <= parents.first.fitness)
         {
            parents.second = parents.first;
            parents.first = { individual.first, fitness };
         }
         else if (fitness <= parents.second.fitness)
         {
            parents.second = { individual.first, fitness };
         }
      }

      return { parents.first.id, parents.second.id };
   }

   std::vector<Move> Genetic::crossover(const std::pair<std::vector<Move>, std::vector<Move>>& parentsMoves) const
   {
      size_t crossoverPoint = randomInRange(1, std::min(parentsMoves.first.size(), parentsMoves.second.size()) - 1);
      std::vector<Move> moves;
      for (size_t i = 0; i < crossoverPoint; ++i)
      {
         moves.push_back(parentsMoves.first.at(i));
      }

      for (size_t i = crossoverPoint; i < parentsMoves.second.size(); ++i)
      {
         moves.push_back(parentsMoves.second.at(i));
      }

      //add also random move at the end
      moves.push_back(randomMove());
      return moves;
   }

   void Genetic::mutate(std::vector<Move>& moves, float mutationRate)
   {
      for (auto& move : moves)
      {
         float mutationDist = static_cast<float>(randomInRange(0, 100)) / 100.f;      
         if (mutationDist >= mutationRate)
         {
            continue;
         }

         move = randomMove();
      }
   }
}