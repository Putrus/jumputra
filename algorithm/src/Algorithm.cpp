#include "../inc/Algorithm.hpp"
#include "../inc/Dummy.hpp"
#include "../inc/Greedy.hpp"

#include <fstream>

namespace jp::algorithm
{
   Algorithm::Algorithm(const std::shared_ptr<logic::Engine>& engine) : mEngine(engine) {}

   void Algorithm::saveMoves(const std::string &filename) const
   {
      nlohmann::json json;
      for (const auto& move : mMoves)
      {
         json["moves"].push_back(move.toJson());
      }
      std::ofstream file(filename);
      file << json;
      file.close();
   }
}