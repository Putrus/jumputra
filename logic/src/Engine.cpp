#include "../inc/Engine.hpp"
#include "../inc/DiagonalSegment.hpp"
#include "../inc/HorizontalSegment.hpp"
#include "../inc/SegmentsConnector.hpp"
#include "../inc/VerticalSegment.hpp"

#include <chrono>
#include <fstream>
#include <thread>

namespace jp::logic
{
   Engine::Engine(const Properties& properties) 
      : mProperties(properties) {}

   Engine::Engine(const Properties& properties, const std::string& worldFilename)
      : mProperties(properties)
   {
      loadFromJsonFile(worldFilename);
   }

   void Engine::update(float dt)
   {
      mStatistics.time += dt;
      for (auto& wind : mWinds)
      {
         wind->update(dt);
      }

      for (auto& character : mCharacters)
      {
         character->update(dt);
         if (mGoal->checkWin(character->getRect()))
         {
            mWinner = character;
            break;
         }
      }
   }

   void Engine::fromJson(const nlohmann::json& json)
   {
      if (json.find("totalStatistics") != json.end())
      {
         mStatistics.fromJson(json["totalStatistics"]);
      }
      
      goalFromJson(json);
      charactersFromJson(json);
      segmentsFromJson(json);
      windsFromJson(json);
   }

   nlohmann::json Engine::toJson() const
   {
      nlohmann::json json;
      json["totalStatistics"] = mStatistics.toJson();
      json["goal"] = mGoal->toJson();
      for (const auto& character : mCharacters)
      {
         json["characters"].push_back(character->toJson());
      }

      for (const auto& segment : mSegments)
      {
         nlohmann::json jsonSegment = segment->toJson();
         jsonSegment["type"] = "segment";
         json["segments"].push_back(jsonSegment);
      }

      for (const auto& wind : mWinds)
      {
         json["winds"].push_back(wind->toJson());
      }
      return json;
   }

   void Engine::addCharacter(const math::Rect<float>& rect)
   {
      mCharacters.push_back(std::make_shared<Character>(rect, mProperties, mStatistics, mSegments, mWinds));
   }

   void Engine::addCharacterCopy(const Character& character)
   {
      mCharacters.push_back(std::make_shared<Character>(character));
   }

   void Engine::removeCharacter(const std::shared_ptr<Character>& character)
   {
      mCharacters.erase(std::find(mCharacters.begin(), mCharacters.end(), character));
   }

   void Engine::removeAllCharacters()
   {
      mCharacters.clear();
   }

   void Engine::removeAllCharactersExcept(const std::shared_ptr<Character>& character)
   {
      mCharacters.erase(std::remove_if(mCharacters.begin(), mCharacters.end(), [&character](const auto& otherCharacter)
         {
            return otherCharacter != character;
         }), mCharacters.end());
   }

   void Engine::resetWinds()
   {
      for (auto& wind : mWinds)
      {
         wind->reset();
      }
   }

   void Engine::saveStatistics(const std::string& filename) const
   {
      nlohmann::json json;
      json["totalStatistics"] = mStatistics.toJson();
      std::ofstream file(filename);
      file << json;
      file.close();
   }

   const std::shared_ptr<Character>& Engine::getWinner() const
   {
      return mWinner;
   }

   std::vector<std::shared_ptr<Character>>& Engine::characters()
   {
      return mCharacters;
   }

   const std::vector<std::shared_ptr<Character>>& Engine::getCharacters() const
   {
      return mCharacters;
   }

   std::vector<std::shared_ptr<Wind>>& Engine::winds()
   {
      return mWinds;
   }

   const std::vector<std::shared_ptr<Wind>>& Engine::getWinds() const
   {
      return mWinds;
   }

   const Properties& Engine::getProperties() const
   {
      return mProperties;
   }

   const Statistics& Engine::getStatistics() const
   {
      return mStatistics;
   }

   std::shared_ptr<logic::Segment> Engine::getSegmentByPosition(const math::Vector2<float>& a)
   {
      auto find = std::find_if(mSegments.begin(), mSegments.end(), [a](const auto& segment)
         {
            return segment->a == a;
         });
      if (find != mSegments.end())
      {
         return *find;
      }

      return nullptr;
   }

   void Engine::setProperties(const Properties& properties)
   {
      mProperties = properties;
   }

   void Engine::goalFromJson(const nlohmann::json& json)
   {
      if (json.find("goal") == json.end())
      {
         return;
      }

      setGoal(json["goal"]);
   }

   void Engine::charactersFromJson(const nlohmann::json& json)
   {
      if (json.find("characters") == json.end())
      {
         return;
      }

      for (const auto& jsonCharacter : json.at("characters"))
      {
         addCharacter(jsonCharacter);
      }
   }

   void Engine::segmentsFromJson(const nlohmann::json& json)
   {      
      if (json.find("segments") == json.end())
      {
         return;
      }

      std::vector<std::shared_ptr<Segment>> mTemporarySegments;
      for (const auto& jsonSegment : json.at("segments"))
      {
         if (jsonSegment.at("type") == "comment")
         {
            continue;
         }

         SegmentSurface surface = SegmentSurface::Ordinary;
         if (jsonSegment.at("surface") == "ordinary" || jsonSegment.at("surface") == SegmentSurface::Ordinary)
         {
            surface = SegmentSurface::Ordinary;
         }
         else if (jsonSegment.at("surface") == "slippery" || jsonSegment.at("surface") == SegmentSurface::Slippery)
         {
            surface = SegmentSurface::Slippery;
         }
         else if (jsonSegment.at("surface") == "sticky" || jsonSegment.at("surface") == SegmentSurface::Sticky)
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
               mTemporarySegments.push_back(Segment::create(a, b, surface));
            }
         }
         else if (jsonSegment.at("type") == "segment")
         {
            math::Vector2<float> a(jsonSegment.at("a"));
            math::Vector2<float> b(jsonSegment.at("b"));
            mTemporarySegments.push_back(Segment::create(a, b, surface));
         }
         else if (jsonSegment.at("type") == "rectangle")
         {
            math::Rect<float> rect(jsonSegment);
            mTemporarySegments.push_back(Segment::create(rect.getLeftTop(), rect.getRightTop(), surface));
            mTemporarySegments.push_back(Segment::create(rect.getRightTop(), rect.getRightBottom(), surface));
            mTemporarySegments.push_back(Segment::create(rect.getLeftBottom(), rect.getRightBottom(), surface));
            mTemporarySegments.push_back(Segment::create(rect.getLeftTop(), rect.getLeftBottom(), surface));
         }
         else
         {
            throw std::runtime_error("jp::logic::Engine::segmentsFromJson - Wrong segment type, failed to load segment");
         }
      }

      SegmentsConnector::connect(mTemporarySegments);

      for (const auto& segment : mTemporarySegments)
      {
         addSegment(segment->a, segment->b, segment->getSurface());
      }

      std::sort(mSegments.begin(), mSegments.end(), [](const auto& lhs, const auto& rhs)
         {
            auto getTypePriority = [](const auto& segment)
               {
                  if (segment->isHorizontal())
                  {
                     return 0;
                  }
                  else if (segment->isVertical())
                  {
                     return 1;
                  }
                  else
                  {
                     return 2;
                  }
               };
            return getTypePriority(lhs) < getTypePriority(rhs);
         });
   }
   
   void Engine::windsFromJson(const nlohmann::json& json)
   {
      if (json.find("winds") == json.end())
      {
         return;
      }

      for (const auto& jsonWind : json.at("winds"))
      {
         addWind(jsonWind);
      }
   }

   void Engine::setGoal(const nlohmann::json& json)
   {
      mGoal = Goal::create(json);
   }

   void Engine::addCharacter(const nlohmann::json& json)
   {
      mCharacters.push_back(Character::create(json, mProperties, mStatistics, mSegments, mWinds));
   }

   void Engine::addSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
   {
      mSegments.push_back(Segment::create(a, b, surface));
   }

   void Engine::addWind(const nlohmann::json& json)
   {
      mWinds.push_back(Wind::create(json));
   }
}