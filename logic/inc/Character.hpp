#pragma once

#include "Entity.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Wind.hpp"

#include <vector>

namespace jp::logic
{
   enum class CharacterState : int
   {
      Dying = 0,
      Falling,
      Flying,
      Running,
      Sledding,
      Sliding,
      Squatting,
      Standing,
      Sticking,
      Stopping
   };

   enum class CharacterDirection : int
   {
      Up = 0,
      Left,
      Right
   };

   std::ostream& operator<<(std::ostream& os, CharacterState state);

   class Character : public Entity
   {
   public:
      Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
         const Properties &properties,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);
      Character(const math::Rect<float>& rect,
         const Properties &properties,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);

      void update(float dt) override;
      void jump();
      void run(CharacterDirection direction);
      void squat();
      void stop();

      virtual void setState(CharacterState state);
      CharacterState getState() const;

   private:
      void resetJumpPower();

      bool canRun() const;
      bool canSquat() const;

      CharacterDirection getDirection() const;
      float getRunSpeed() const;
      
      void setDirection(CharacterDirection direction);
      void setRunSpeed(float speed);

      CharacterState mState = CharacterState::Flying;
      CharacterDirection mDirection = CharacterDirection::Up;
      math::Vector2<float> mJumpPower = math::Vector2<float>();
      float mRunSpeed = 0.f;

      const Properties& mProperties;
      const std::vector<std::shared_ptr<Segment>>& mSegments;
      const std::vector<std::shared_ptr<Wind>>& mWinds;
   };
}