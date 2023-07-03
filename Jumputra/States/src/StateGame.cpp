#include "../inc/StateGame.h"

#include <json/json.h>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context), mGame(context)
   {
      loadLastJson();
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mGame, states);
   }

   bool StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         float height = static_cast<float>(mContext.window.getSize().y);
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         }
      }

      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
            //to do
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      return mGame.update(dt);
   }

   void StateGame::loadLastJson()
   {
      std::string directory = "StaticObjects";
      std::filesystem::path newestPath;
      for (const auto& entry : std::filesystem::directory_iterator(directory))
      {
         if (std::filesystem::is_regular_file(entry) && entry.path().extension() == ".json" && (!std::filesystem::exists(newestPath) ||
            std::filesystem::last_write_time(entry.path()) > std::filesystem::last_write_time(newestPath)))
         {
            newestPath = entry.path();
         }
      }

      if (std::filesystem::exists(newestPath))
      {
         std::ifstream file(newestPath.string());
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
}