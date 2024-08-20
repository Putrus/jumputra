#pragma once

#include "Entity.hpp"

#include "../../core/inc/Jsonable.hpp"

#include <memory>

namespace jp::logic
{
   class Wind : public Entity
   {
   public:
      Wind(float impact, const math::Vector2<float>& maxVelocity,
         const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
         const math::Vector2<float>& velocity = 0.f);
      Wind(const nlohmann::json& json);

      Wind& operator=(const Wind& other);

      static std::shared_ptr<Wind> create(const nlohmann::json& json);

      virtual void update(float dt) override;
      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      float getImpact() const;
      const math::Vector2<float>& getMaxVelocity() const;

      void setMaxVelocity(const math::Vector2<float>& maxVelocity);

   private:
      float mImpact = 0.f;
      math::Vector2<float> mMaxVelocity = 0.f;
   };
}