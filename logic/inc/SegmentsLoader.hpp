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
      for (const auto& jsonSegment : json.at("segments"))
      {
         if (jsonSegment.at("type") == "comment")
         {
            continue;
         }

         SegmentSurface surface = SegmentSurface::Ordinary;
         if (jsonSegment.at("surface") == "ordinary")
         {
            surface = SegmentSurface::Ordinary;
         }
         else if (jsonSegment.at("surface") == "slippery")
         {
            surface = SegmentSurface::Slippery;
         }
         else if (jsonSegment.at("surface") == "sticky")
         {
            surface = SegmentSurface::Sticky;
         }
         else
         {
            throw std::runtime_error("jp::logic::SegmentsLoader::loadFromJson - Wrong surface type, failed to load segment");
         }

         if (jsonSegment.at("type") == "points")
         {
            const auto& jsonPoints = jsonSegment.at("points");
            for (size_t i = 1; i < jsonPoints.size(); ++i)
            {
               math::Vector2<float> a(jsonPoints.at(i - 1).at("x"), jsonPoints.at(i - 1).at("y"));
               math::Vector2<float> b(jsonPoints.at(i).at("x"), jsonPoints.at(i).at("y"));
               segments.push_back(T::create(a, b, surface));
            }
         }
         else if (jsonSegment.at("type") == "segment")
         {
            //TODO
         }
         else if (jsonSegment.at("type") == "rectangle")
         {
            math::Rect<float> rect(jsonSegment.at("left"), jsonSegment.at("top"),
               jsonSegment.at("width"), jsonSegment.at("height"));
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