#pragma once

#include "Character.hpp"

#include "../physics/inc/Engine.hpp"

namespace jp::game
{
    class Game
    {


    private:
        std::vector<Character> mCharacters;

        physics::Engine mEngine;
    };
}