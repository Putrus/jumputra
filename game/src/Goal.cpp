#include "../inc/Goal.hpp"

namespace jp::game
{
   Goal::Goal(const math::Rect<float>& rect)
      : graphics::Goal(rect), logic::Goal(rect) {}

   Goal::Goal(const nlohmann::json& json)
      : graphics::Goal(json), logic::Goal(json) {}

   std::shared_ptr<Goal> Goal::create(const nlohmann::json& json)
   {
      return std::make_shared<Goal>(json);
   }
}