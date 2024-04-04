#pragma once

#include "../inc/Segment.hpp"

#include <nlohmann/json.hpp>

#include <vector>

namespace jp::logic
{
   template <typename T>
   class SegmentsLoader
   {
   public:
      std::vector<std::shared_ptr<T>> loadFromFile(const std::string &filename) const;
      std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const;
   };

   template <typename T>
   std::vector<std::shared_ptr<T>> SegmentsLoader<T>::loadFromFile(const std::string &filename) const
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::SegmentsLoader::loadFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      return loadFromJson(data);
   }

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
            throw std::runtime_error("jp::logic::SegmentsLoader::loadSegmentsFromJson - Wrong surface type, failed to load segment");
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
            segments.push_back(T::create(rect.getLeftSegmentop(), rect.getRightSegmentop(), surface));
            segments.push_back(T::create(rect.getRightSegmentop(), rect.getRightBottom(), surface));
            segments.push_back(T::create(rect.getLeftBottom(), rect.getRightBottom(), surface));
            segments.push_back(T::create(rect.getLeftSegmentop(), rect.getLeftBottom(), surface));
         }
         else
         {
            //TODO
         }
      }

      return segments;
   }
}