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

   protected:
      virtual void draw() const;
      virtual void event();

      Properties mProperties;

      std::vector<std::shared_ptr<Character>> mCharacters;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;
   };
}