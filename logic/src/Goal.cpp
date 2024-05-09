#include "../inc/Goal.hpp"

namespace jp::logic
{
   Goal::Goal(const math::Rect<float>& rect) : mRect(rect) {}

   void Goal::fromJson(const nlohmann::json& json)
   {
      mRect = json["rect"];
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