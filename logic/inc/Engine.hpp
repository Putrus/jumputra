#pragma once

#include "Character.hpp"
#include "Goal.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Updatable.hpp"
#include "Wind.hpp"

namespace jp::logic
{
   class Engine : public Updatable, public core::Jsonable
   {
   public:
      Engine(const Properties& properties);

      virtual void update(float dt) override;
      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      void setGoal(const std::shared_ptr<Goal>& goal);
      void addCharacter(const std::shared_ptr<Character>& character);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

      void saveStatistics(const std::string& filename) const;
      
      bool hasGoalBeenAchieved() const;

   protected:
      void goalFromJson(const nlohmann::json& json);
      void charactersFromJson(const nlohmann::json& json);
      void segmentsFromJson(const nlohmann::json& json);
      void windsFromJson(const nlohmann::json& json);

      virtual void setGoal(const nlohmann::json& json);
      virtual void addCharacter(const nlohmann::json& json);
      virtual void addSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);
      virtual void addWind(const nlohmann::json& json);

      Properties mProperties;

      std::shared_ptr<Goal> mGoal;
      std::vector<std::shared_ptr<Character>> mCharacters;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;

      bool mGoalHasBeenAchieved = false;
   };
}