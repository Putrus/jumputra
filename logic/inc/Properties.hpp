#pragma once

#include "../../math/inc/Vector2.hpp"

#include <nlohmann/json.hpp>

namespace jp::logic
{
   struct Properties
   {
      void loadFromFile(const std::string& filename);
      void loadFromJson(const nlohmann::json& json);

      struct Graphic
      {
         struct Window
         {
            math::Vector2<unsigned int> size;
         } window;
      } graphic;

      struct Logic
      {
         float secondsPerUpdate = 0.f;

         struct Character
         {
            struct Jump
            {
               math::Vector2<float> gain = 0.f;
               math::Vector2<float> max = 0.f;
            } jump;
            float runSpeed = 0.f;
         } character;

         struct Physics
         {
            float bounceFactor = 0.f;
            float checkCollisionDistance = 0.f;
            float fallSpeed = 0.f;
            float slipperyFriction = 0.f;
            math::Vector2<float> gravity = 0.f;
         } physics;
      } logic;
   };
}