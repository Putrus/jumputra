#pragma once

#include "Character.hpp"
#include "Goal.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Updatable.hpp"
#include "Wind.hpp"

#include <atomic>

namespace jp::logic
{
   class Engine : public Updatable, public core::Jsonable
   {
   public:
      Engine(const Properties& properties);
      Engine(const Properties& properties, const std::string& worldFilename);

      virtual void update(float dt) override;
      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      virtual void addCharacter(const math::Rect<float>& rect);
      virtual void addCharacterCopy(const Character& character);
      virtual void removeCharacter(const std::shared_ptr<Character>& character);
      virtual void removeAllCharacters();
      virtual void removeAllCharactersExcept(const std::shared_ptr<Character>& character);

      void resetWinds();

      void saveStatistics(const std::string& filename) const;

      const std::shared_ptr<Character>& getWinner() const;
      std::vector<std::shared_ptr<Character>>& characters();
      const std::vector<std::shared_ptr<Character>>& getCharacters() const;
      std::vector<std::shared_ptr<Wind>>& winds();
      const std::vector<std::shared_ptr<Wind>>& getWinds() const;
      const Properties& getProperties() const;
      const Statistics& getStatistics() const;
      std::shared_ptr<logic::Segment> getSegmentByPosition(const math::Vector2<float>& a);

      void setProperties(const Properties& properties);

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
      Statistics mStatistics;

      std::shared_ptr<Goal> mGoal;
      std::shared_ptr<Character> mWinner;
      std::vector<std::shared_ptr<Character>> mCharacters;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;
   };
}