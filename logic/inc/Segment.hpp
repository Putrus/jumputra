#pragma once

#include "../../math/inc/Segment.hpp"
#include "../../math/inc/Rect.hpp"

#include <iostream>
#include <memory>

namespace jp::logic
{
   enum class SegmentSurface : unsigned long long
   {
      Ordinary = 0,
      Slippery,
      Sticky
   };

   std::ostream& operator<<(std::ostream& os, SegmentSurface surface);

   enum class SegmentCollision : unsigned long long
   {
      No = 0,
      Top,
      Bottom,
      Left,
      Right,
      Attic,
      Roof
   };

   std::ostream& operator<<(std::ostream& os, SegmentCollision collision);

   class Segment : public math::Segment<float>
   {
   public:
      Segment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);

      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      static std::shared_ptr<Segment> create(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      static std::shared_ptr<Segment> create(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);

      virtual SegmentCollision checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const = 0;

      SegmentSurface getSurface() const;

      void setSurface(SegmentSurface surface);

   private:
      SegmentSurface mSurface;
   };
}