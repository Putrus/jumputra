#pragma once

#include "Character.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Updatable.hpp"
#include "Wind.hpp"

namespace jp::logic
{
   class Engine : public Updatable
   {
   public:
      Engine(const std::string& dataPath = "data");
      Engine(const Properties& properties);

      void run();
      virtual void update(float dt) override;

      void addCharacter(const std::shared_ptr<Character>& character);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

   protected:
      virtual void draw();
      virtual void event();

      Properties mProperties;

      std::vector<std::shared_ptr<Character>> mCharacters;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;
   };
}