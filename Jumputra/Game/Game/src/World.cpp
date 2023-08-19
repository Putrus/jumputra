#include "../inc/World.h"

#include <json/json.h>
#include <json/json-forwards.h>

#include <fstream>

namespace jp::game
{
   World::World(const Context& context)
   {
      loadJson();
   }

   void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const physics::StaticObject& object : mStatics)
      {
         target.draw(object, states);
      }

      for (const physics::DynamicObject& character : mDynamics)
      {
         target.draw(character, states);
      }
   }

   bool World::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch(event.key.code)
         {
         }
      }

      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
         }
      }
      return true;
   }

   bool World::update(const sf::Time& dt)
   {
      for (physics::DynamicObject& character : mDynamics)
      {
         character.update(dt, mStatics);
      }
      return true;
   }

   void World::loadJson()
   {
      std::ifstream file(WORLD_JSON);
      if (file.is_open())
      {
         mStatics.clear();
         Json::Value jsonObjects;
         file >> jsonObjects;
         for (const auto& jsonObject : jsonObjects)
         {
            mStatics.push_back(game::physics::StaticObject(sf::FloatRect(jsonObject["left"].asFloat(),
               jsonObject["top"].asFloat(), jsonObject["width"].asFloat(), jsonObject["height"].asFloat())));
         }
         file.close();
      }
   }
}