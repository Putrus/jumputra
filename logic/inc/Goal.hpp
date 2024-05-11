#pragma once

#include "../../math/inc/Rect.hpp"

namespace jp::logic
{
   class Goal : public core::Jsonable
   {
   public:
      Goal(const math::Rect<float>& rect);
      Goal(const nlohmann::json& json);

      static std::shared_ptr<Goal> create(const nlohmann::json& json);

      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;
      
      bool checkWin(const math::Rect<float>& rect) const;

   private:
      math::Rect<float> mRect;
   };
}