#pragma once

#include "Movable.hpp"

#include "../../logic/inc/Engine.hpp"

namespace jp::algorithm
{
   class Algorithm : public Movable
   {
   public:
      Algorithm(const std::shared_ptr<logic::Engine>& engine);

      void saveMoves(const std::string &filename) const;

   protected:
      std::shared_ptr<logic::Engine> mEngine;
   };
}