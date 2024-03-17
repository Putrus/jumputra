#pragma once

#include "Properties.hpp"

#include "../../inc/Updatable.hpp"

namespace jp::game::physics
{
   class Physics : public Updatable
   {
   public:
      Physics(const Properties& properties);

      void update(float dt) override;
   };
}