#include "../inc/Game.hpp"

#include <iostream>

int main()
{
   try
   {
      jp::game::Game game;
      game.run();   
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
   }
   
   return 0;
}