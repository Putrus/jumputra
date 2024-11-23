#pragma once

#include "Entity.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Statistics.hpp"
#include "Wind.hpp"

#include <vector>

namespace jp::logic
{
   enum class CharacterState : int
   {
      Burying = 0,
      Dying,
      Falling,
      Flying,
      Lying,
      Running,
      Sledding,
      Sliding,
      Squatting,
      Standing,
      Sticking
   };

   std::ostream& operator<<(std::ostream& os, CharacterState state);

   enum class CharacterDirection : int
   {
      Up = 0,
      Left,
      Right
   };

   std::ostream& operator<<(std::ostream& os, CharacterDirection direction);

   class Character : public Entity
   {
   public:
      Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
         const Properties& properties,
         Statistics& totalStatistics,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);
      Character(const math::Rect<float>& rect,
         const Properties& properties,
         Statistics& totalStatistics,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);
      Character(const nlohmann::json& json,
         const Properties& properties,
         Statistics& totalStatistics,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);
      Character(const Character& other);

      Character& operator=(const Character& other);

      static std::shared_ptr<Character> create(const nlohmann::json& json,
         const Properties& properties,
         Statistics& totalStatistics,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);

      static CharacterDirection oppositeDirection(CharacterDirection direction);

      void update(float dt) override;
      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;
      
      void jump();
      void run(CharacterDirection direction);
      void squat();
      void stop();
      void reset(const math::Rect<float>& rect);
      
      void setDirection(CharacterDirection direction);
      void setRunSpeed(float speed);

      CharacterDirection getDirection() const;
      CharacterState getState() const;
      float getRunSpeed() const;
      Statistics getStatistics() const;
      const std::vector<std::shared_ptr<logic::Segment>>& getVisitedSegments() const;
      std::vector<std::shared_ptr<logic::Segment>> getVisitedHorizontalSegments() const;
      std::vector<std::shared_ptr<logic::Segment>> getVisitedDiagonalSegments() const;
      std::vector<std::shared_ptr<logic::Segment>> getVisitedVerticalSegments() const;
      const math::Vector2<float>& getJumpPower() const;
      const Properties& getProperties() const;

      bool canRun() const;
      bool canSquat() const;
      bool isSticked() const;

   protected:
      virtual void setState(CharacterState state);

   private:
      void resetJumpPower();

      CharacterState mState = CharacterState::Flying;
      CharacterDirection mDirection = CharacterDirection::Up;
      math::Vector2<float> mJumpPower = math::Vector2<float>();
      math::Vector2<float> mGravity = math::Vector2<float>();
      std::vector<std::shared_ptr<logic::Segment>> mVisitedSegments;
      float mRunSpeed = 0.f;
      Statistics mStatistics;

      const Properties& mProperties;
      Statistics& mTotalStatistics;
      const std::vector<std::shared_ptr<Segment>>& mSegments;
      const std::vector<std::shared_ptr<Wind>>& mWinds;
   };
}