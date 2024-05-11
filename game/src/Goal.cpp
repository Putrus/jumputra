#include "../inc/Goal.hpp"

namespace jp::game
{
   Goal::Goal(const math::Rect<float>& rect)
      : graphic::Goal(rect), logic::Goal(rect) {}

   Goal::Goal(const nlohmann::json& json)
      : graphic::Goal(json), logic::Goal(json) {}

   std::shared_ptr<Goal> Goal::create(const nlohmann::json& json)
   {
      return std::make_shared<Goal>(json);
   }
}