#pragma once

#include "PhysicsProperties.hpp"

#include "../../inc/Updatable.hpp"

namespace jp::game::physics
{
   class Physics : public Updatable
   {
   public:
      Physics(const PhysicsProperties& properties);

      void update(float dt) override;
   };
}