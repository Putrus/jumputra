#include "../inc/SegmentsLoader.hpp"

#include "../../physics/inc/DiagonalSegment.hpp"
#include "../../physics/inc/HorizontalSegment.hpp"
#include "../../physics/inc/VerticalSegment.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game::json
{
   std::vector<std::shared_ptr<physics::Segment>> SegmentsLoader::loadSegments(const std::string& filename)
   {
      std::vector<std::shared_ptr<physics::Segment>> segments;

      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::invalid_argument("SegmentsLoader::loadSegments - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;

      for (const auto& jsonSegment : data["segments"])
      {
         if (jsonSegment["type"] == "comment")
         {
            continue;
         }

         physics::SegmentSurface surface = physics::SegmentSurface::Ordinary;
         std::string strSurface = jsonSegment["surface"];
         if (strSurface == "slippery")
         {
            surface = physics::SegmentSurface::Slippery;
         }
         else if (strSurface == "sticky")
         {
            surface = physics::SegmentSurface::Sticky;
         }
         else if (strSurface == "ordinary")
         {
            surface = physics::SegmentSurface::Ordinary;
         }
         else
         {
            throw std::runtime_error("SegmentsLoader::loadSegments - Surface " + filename + " doesn't exist");
         }

         std::string strType = jsonSegment["type"];
         if (strType == "points")
         {
            const auto& jsonPoints = jsonSegment["points"];
            for (size_t i = 1; i < jsonPoints.size(); ++i)
            {
               math::Vector2<float> a(jsonPoints[i - 1]["x"], jsonPoints[i - 1]["y"]);
               math::Vector2<float> b(jsonPoints[i]["x"], jsonPoints[i]["y"]);
               segments.push_back(createSegment(a, b, surface));
            }
         }
         else if (strType == "rectangle")
         {
            math::Rect<float> rect(jsonSegment["left"], jsonSegment["top"],
               jsonSegment["width"], jsonSegment["height"]);

            segments.push_back(createSegment(rect.getLeftTop(), rect.getRightTop(), surface));
            segments.push_back(createSegment(rect.getRightTop(), rect.getRightBottom(), surface));
            segments.push_back(createSegment(rect.getLeftBottom(), rect.getRightBottom(), surface));
            segments.push_back(createSegment(rect.getLeftTop(), rect.getLeftBottom(), surface));
         }
         else
         {
            throw std::runtime_error("SegmentsLoader::loadSegments - Wrong segment type " + strType);
         }
      }

      file.close();

      return segments;
   }

   std::shared_ptr<physics::Segment> SegmentsLoader::createSegment(const math::Vector2<float>& a,
        const math::Vector2<float>& b, physics::SegmentSurface surface)
   {
      math::Segment<float> segment(a, b);
      if (segment.isVertical())
      {
         return std::make_unique<physics::VerticalSegment>(a, b, surface);
      }
      else if (segment.isHorizontal())
      {
         return std::make_unique<physics::HorizontalSegment>(a, b, surface);
      }
      else if (segment.isDiagonal())
      {
         return std::make_unique<physics::DiagonalSegment>(a, b, surface);
      }
      else
      {
         throw std::runtime_error("SegmentsLoader::createSegment - Failed to create a segment. The platform is neither horizontal, nor vertical, nor diagonal");
      }
      return nullptr;
   }
}