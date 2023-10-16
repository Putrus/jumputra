#include "CharacterProperties.hpp"

#include "../../physics/inc/PhysicsProperties.hpp"

namespace jp::game::engine
{
   class Properties
   {
   public:
      void load();
      void save();

      const CharacterProperties& getCharacterProperties();
      const CharacterProperties& getPhysicsProperties();

      friend class GameEngine;
   private:
      CharacterProperties mCharacterProperties;
      physics::PhysicsProperties mPhysicsProperties;
   };
}