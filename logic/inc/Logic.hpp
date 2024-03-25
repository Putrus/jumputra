#pragma once

#include "../inc/Character.hpp"
#include "../../inc/Properties.hpp"

#include "../../physics/inc/Physics.hpp"

namespace jp::game::logic
{
   class Logic : public Updatable
   {
   public:
      Logic(const ::jp::game::Properties& properties);

      void run();
      virtual void update(float dt) override;

      void addCharacter(const std::shared_ptr<Character>& character);

   protected:
      virtual void draw() const;
      virtual void event();

   private:
      const Properties& mProperties;

      std::vector<std::shared_ptr<Character>> mCharacters;
      std::unique_ptr<physics::Physics> mPhysics;

      
   };
}