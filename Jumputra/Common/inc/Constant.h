#pragma once

namespace jp
{
   constexpr const char* FONTS_DIR = "Data/Resources/Fonts/";
   constexpr const char* TEXTURES_DIR = "Data/Resources/Textures/";
   constexpr const char* SOUND_BUFFERS_DIR = "Data/Resources/SoundBuffers/";

   constexpr const char* CHARACTERS_JSON = "Data/Jsons/Characters.json";
   constexpr const char* WORLD_JSON = "Data/Jsons/World.json";

   constexpr float GRAVITY = 1000.f;
   constexpr float BOUNCE_FACTOR = 0.4f;
   constexpr float SECONDS_PER_FRAME = 1.f / 120.f;
   constexpr float JUMP_VELOCITY_X = 300.f;
   constexpr float JUMP_VELOCITY_Y = -533.f;
   constexpr float MAX_JUMP_VELOCITY_Y = -800.f;
   constexpr float GROUND_VELOCITY_X = 150.f;

   constexpr unsigned int WINDOW_SIZE_X = 1280;
   constexpr unsigned int WINDOW_SIZE_Y = 720;
}