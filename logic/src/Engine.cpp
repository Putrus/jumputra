#include "../inc/Engine.hpp"
#include "../inc/DiagonalSegment.hpp"
#include "../inc/HorizontalSegment.hpp"
#include "../inc/VerticalSegment.hpp"

#include <chrono>

namespace jp::logic
{
   Engine::Engine(const logic::Properties& properties) 
      : mProperties(properties) {}

   void Engine::update(float dt)
   {
      for (auto& wind : mWinds)
      {
         wind->update(dt);
      }
      
      for (auto& character : mCharacters)
      {
         character->update(dt);
      }
   }

   void Engine::fromJson(const nlohmann::json& json)
   {
      charactersFromJson(json);
      segmentsFromJson(json);
      windsFromJson(json);
   }

   nlohmann::json Engine::toJson() const
   {
      nlohmann::json json;
      
      return json;
   }

   void Engine::setGoal(const std::shared_ptr<Goal>& goal)
   {
      mGoal = goal;
   }

   void Engine::addCharacter(const std::shared_ptr<Character>& character)
   {
      mCharacters.push_back(character);
   }

   void Engine::addSegment(const std::shared_ptr<Segment>& segment)
   {
      mSegments.push_back(segment);
   }

   void Engine::addWind(const std::shared_ptr<Wind>& wind)
   {
      mWinds.push_back(wind);
   }

   void Engine::charactersFromJson(const nlohmann::json& json)
   {
      for (const auto& jsonCharacter : json.at("characters"))
      {
         addCharacter(createCharacter(jsonCharacter));
      }
   }

   void Engine::segmentsFromJson(const nlohmann::json& json)
   {
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
            throw std::runtime_error("jp::logic::Engine::segmentsFromJson - Wrong surface type, failed to load segment");
         }

         if (jsonSegment.at("type") == "points")
         {
            const auto& jsonPoints = jsonSegment.at("points");
            for (size_t i = 1; i < jsonPoints.size(); ++i)
            {
               math::Vector2<float> a(jsonPoints.at(i - 1));
               math::Vector2<float> b(jsonPoints.at(i));
               addSegment(createSegment(a, b, surface));
            }
         }
         else if (jsonSegment.at("type") == "segment")
         {
            math::Vector2<float> a(jsonSegment.at("a"));
            math::Vector2<float> b(jsonSegment.at("b"));
            addSegment(createSegment(a, b, surface));
         }
         else if (jsonSegment.at("type") == "rectangle")
         {
            math::Rect<float> rect(jsonSegment);
            addSegment(createSegment(rect.getLeftTop(), rect.getRightTop(), surface));
            addSegment(createSegment(rect.getRightTop(), rect.getRightBottom(), surface));
            addSegment(createSegment(rect.getLeftBottom(), rect.getRightBottom(), surface));
            addSegment(createSegment(rect.getLeftTop(), rect.getLeftBottom(), surface));
         }
         else
         {
            throw std::runtime_error("jp::logic::Engine::segmentsFromJson - Wrong segment type, failed to load segment");
         }
      }
   }
   
   void Engine::windsFromJson(const nlohmann::json& json)
   {
      for (const auto& jsonWind : json.at("winds"))
      {
         addWind(createWind(jsonWind));
      }
   }

   std::shared_ptr<Character> Engine::createCharacter(const nlohmann::json& json) const
   {
      return std::make_shared<Character>(json, mProperties, mSegments, mWinds);
   }

   std::shared_ptr<Segment> Engine::createSegment(const math::Vector2<float>& a,
      const math::Vector2<float>& b, SegmentSurface surface) const
   {
      math::Segment<float> segment(a.x, a.y, b.x, b.y);
      if (segment.isDiagonal())
      {
         return std::make_shared<DiagonalSegment>(a.x, a.y, b.x, b.y, surface);
      }
      else if (segment.isHorizontal())
      {
         return std::make_shared<HorizontalSegment>(a.x, a.y, b.x, b.y, surface);
      }
      else if (segment.isVertical())
      {
         return std::make_shared<VerticalSegment>(a.x, a.y, b.x, b.y, surface);
      }
      else
      {
         throw std::invalid_argument("jp::logic::Engine::createSegment - Failed to create segment, wrong arguments");
      }
   }

   std::shared_ptr<Wind> Engine::createWind(const nlohmann::json& json) const
   {
      return std::make_shared<Wind>(json);
   }
}