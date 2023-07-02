#include "../inc/StateCreator.h"

#include <json/json.h>
#include <json/json-forwards.h>
#include <jsoncpp.cpp>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace jp::state
{
   StateCreator::StateCreator(StateStack* stack, const Context& context) : State(stack, context),
      mView(sf::FloatRect(0.f, 0.f, static_cast<float>(context.window.getSize().x),
         static_cast<float>(context.window.getSize().y)))
   {
      mSelectedRect.setOutlineColor(sf::Color::Red);
      mSelectedRect.setOutlineThickness(3.f);
      mSelectedRect.setFillColor(sf::Color::Transparent);
   }

   void StateCreator::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mSelectedRect, states);
      for (const auto& object : mObjects)
      {
         target.draw(object, states);
      }
   }

   bool StateCreator::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            resetView();
            popState();
            pushState(StateID::Menu);
            break;
         case sf::Keyboard::Up:
            moveView(-static_cast<float>(mContext.window.getSize().y));
            break;
         case sf::Keyboard::Down:
            moveView(static_cast<float>(mContext.window.getSize().y));
            break;
         case sf::Keyboard::S:
            saveJson();
            break;
         case sf::Keyboard::L:
            loadLastJson();
            break;
         }
      }
      if (event.type == sf::Event::MouseButtonReleased)
      {
         if (event.key.code == sf::Mouse::Left)
         {
            float mouseX = static_cast<float>(sf::Mouse::getPosition(mContext.window).x);
            float mouseY = static_cast<float>(sf::Mouse::getPosition(mContext.window).y) + mViewVerticalOffset;
            if (mSelected)
            {
               std::cout << mSelectedRect.getPosition().x << " " << mSelectedRect.getPosition().y << " wh: " <<
                  mSelectedRect.getSize().x << " " << mSelectedRect.getSize().y << std::endl;
               mObjects.push_back(game::physics::StaticObject(mSelectedRect.getPosition(), mSelectedRect.getSize()));
               mSelectedRect.setSize(sf::Vector2f(0.f, 0.f));
               mSelected = false;
            }
            else
            {
               mSelectedRect.setPosition(sf::Vector2f(mouseX, mouseY));
               mSelected = true;
            }
         }
         if (event.key.code == sf::Mouse::Right)
         {
            mSelectedRect.setSize(sf::Vector2f(0.f, 0.f));
            mSelected = false;
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

   bool StateCreator::update(const sf::Time& dt)
   {
      if (mSelected)
      {
         float mouseX = static_cast<float>(sf::Mouse::getPosition(mContext.window).x);
         float mouseY = static_cast<float>(sf::Mouse::getPosition(mContext.window).y) + mViewVerticalOffset;
         mSelectedRect.setSize(sf::Vector2f(mouseX, mouseY) - mSelectedRect.getPosition());
      }
      return true;
   }

   void StateCreator::moveView(float offset)
   {
      mViewVerticalOffset += offset;
      mView.move(sf::Vector2f(0.f, offset));
      mContext.window.setView(mView);
   }

   void StateCreator::resetView()
   {
      mView.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(mContext.window.getSize().x),
         static_cast<float>(mContext.window.getSize().y)));
      mContext.window.setView(mView);
   }

   void StateCreator::saveJson() const
   {
      Json::Value jsonRects(Json::arrayValue);
      for (const auto& object : mObjects)
      {
         Json::Value jsonRect;
         jsonRect["left"] = object.getLeft();
         jsonRect["top"] = object.getTop();
         jsonRect["width"] = object.getWidth();
         jsonRect["height"] = object.getHeight();
         jsonRects.append(jsonRect);
      }
      if (!std::filesystem::exists("StaticObjects"))
      {
         std::filesystem::create_directory("StaticObjects");
      }
      std::ofstream file(generateJsonFilename());
      if (file.is_open())
      {
         file << jsonRects;
         file.close();
      }
      else
      {
         throw std::runtime_error("Failed to save json file");
      }
   }

   void StateCreator::loadLastJson()
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

   std::string StateCreator::generateJsonFilename() const
   {
      std::time_t now = std::time(nullptr);
      std::tm* timeinfo = std::localtime(&now);
      char buffer[80];
      std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);
      return "StaticObjects/" + std::string(buffer) + ".json";
   }
}