#pragma once

#include "../../graphics/inc/Goal.hpp"
#include "../../logic/inc/Goal.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Goal : public graphics::Goal, public logic::Goal
   {
   public:
      Goal(const math::Rect<float>& rect);
      Goal(const nlohmann::json& json);

      static std::shared_ptr<Goal> create(const nlohmann::json& json);
   };
}