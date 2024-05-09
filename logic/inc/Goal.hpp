#pragma once

#include "../../math/inc/Rect.hpp"

namespace jp::logic
{
   class Goal : public core::Jsonable
   {
   public:
      Goal(const math::Rect<float>& rect);

      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;
      
      bool checkWin(const math::Rect<float>& rect) const;

   private:
      math::Rect<float> mRect;
   };
}