#include "../inc/Goal.hpp"

namespace jp::logic
{
   Goal::Goal(const math::Rect<float>& rect) : mRect(rect) {}

   Goal::Goal(const nlohmann::json& json)
   {
      fromJson(json);
   }

   std::shared_ptr<Goal> Goal::create(const nlohmann::json& json)
   {
      return std::make_shared<Goal>(json);
   }

   void Goal::fromJson(const nlohmann::json& json)
   {
      mRect = json.at("rect");
   }

   nlohmann::json Goal::toJson() const
   {
      nlohmann::json json;
      json["rect"] = mRect.toJson();
      return json;
   }

   bool Goal::checkWin(const math::Rect<float>& rect) const
   {
      return mRect.intersects(rect);
   }
}