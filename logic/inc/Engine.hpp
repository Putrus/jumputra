#pragma once

#include "Character.hpp"
#include "Properties.hpp"
#include "Runnable.hpp"
#include "Segment.hpp"
#include "Wind.hpp"

namespace jp::logic
{
   class Engine : public Runnable
   {
   public:
      Engine(const Properties& properties);

      void update(float dt) override;

      void draw() override;
      void event() override;

      void addCharacter(const std::shared_ptr<Character>& character);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

   protected:
      Properties mProperties;

      std::vector<std::shared_ptr<Character>> mCharacters;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;
   };
}