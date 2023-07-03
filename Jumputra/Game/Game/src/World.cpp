#include "../inc/World.h"

#include <json/json.h>
#include <json/json-forwards.h>

#include <fstream>

namespace jp::game
{
   World::World(const Context& context)
   {
      mCharacters.push_back(Character("Penguin", context));
      loadJson();
   }

   void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const Character& character : mCharacters)
      {
         target.draw(character, states);
      }

      for (const physics::StaticObject& object : mObjects)
      {
         target.draw(object, states);
      }
   }

   bool World::update(const sf::Time& dt)
   {
      for (Character& character : mCharacters)
      {
         character.update(dt, mObjects);
      }
      return true;
   }

   void World::loadJson()
   {
      std::ifstream file(WORLD_JSON);
      if (file.is_open())
      {
         mObjects.clear();
         Json::Value jsonObjects;
         file >> jsonObjects;
         for (const auto& jsonObject : jsonObjects)
         {
            mObjects.push_back(game::physics::StaticObject(sf::FloatRect(jsonObject["left"].asFloat(),
               jsonObject["top"].asFloat(), jsonObject["width"].asFloat(), jsonObject["height"].asFloat())));
         }
         file.close();
      }
   }
}