#pragma once

namespace jp
{
   constexpr const char* FONTS_DIR = "Data/Resources/Fonts/";
   constexpr const char* TEXTURES_DIR = "Data/Resources/Textures/";
   constexpr const char* SOUND_BUFFERS_DIR = "Data/Resources/SoundBuffers/";

   constexpr const char* CHARACTERS_JSON = "Data/Jsons/Characters.json";
   constexpr const char* WORLD_JSON = "Data/Jsons/World.json";


   constexpr float GRAVITY = 1000.f;
   constexpr float SECONDS_PER_FRAME = 1.f / 90.f;
   constexpr float MAX_JUMP_VELOCITY_Y = 1.f;
   constexpr float VELOCITY_X = 0.1f;

   constexpr unsigned int WINDOW_SIZE_X = 1280;
   constexpr unsigned int WINDOW_SIZE_Y = 720;
}