#pragma once

#include "EntityLoader.hpp"

namespace jp::logic
{
   template <typename T>
   class SegmentsLoader : public EntityLoader<T>
   {
   public:
      std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const;
   };

   template <typename T>
   std::vector<std::shared_ptr<T>> SegmentsLoader<T>::loadFromJson(const nlohmann::json& json) const
   {
      std::vector<std::shared_ptr<T>> segments;
      for (const auto& jsonSegment : json["segments"])
      {
         if (jsonSegment["type"] == "comment")
         {
            continue;
         }

         SegmentSurface surface = SegmentSurface::Ordinary;
         if (jsonSegment["surface"] == "ordinary")
         {
            surface = SegmentSurface::Ordinary;
         }
         else if (jsonSegment["surface"] == "slippery")
         {
            surface = SegmentSurface::Slippery;
         }
         else if (jsonSegment["surface"] == "sticky")
         {
            surface = SegmentSurface::Sticky;
         }
         else
         {
            throw std::runtime_error("jp::logic::SegmentsLoader::loadFromJson - Wrong surface type, failed to load segment");
         }

         if (jsonSegment["type"] == "points")
         {
            const auto& jsonPoints = jsonSegment["points"];
            for (size_t i = 1; i < jsonPoints.size(); ++i)
            {
               math::Vector2<float> a(jsonPoints[i - 1]["x"], jsonPoints[i - 1]["y"]);
               math::Vector2<float> b(jsonPoints[i]["x"], jsonPoints[i]["y"]);
               segments.push_back(T::create(a, b, surface));
            }
         }
         else if (jsonSegment["type"] == "segment")
         {
            //TODO
         }
         else if (jsonSegment["type"] == "rectangle")
         {
            math::Rect<float> rect(jsonSegment["left"], jsonSegment["top"],
               jsonSegment["width"], jsonSegment["height"]);
            segments.push_back(T::create(rect.getLeftTop(), rect.getRightTop(), surface));
            segments.push_back(T::create(rect.getRightTop(), rect.getRightBottom(), surface));
            segments.push_back(T::create(rect.getLeftBottom(), rect.getRightBottom(), surface));
            segments.push_back(T::create(rect.getLeftTop(), rect.getLeftBottom(), surface));
         }
         else
         {
            //TODO
         }
      }

      return segments;
   }
}