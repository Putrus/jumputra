#include "../inc/Jumputra.hpp"

#include <iostream>

int main()
{
   try
   {
      jp::game::Jumputra jumputra;
      jumputra.run();   
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
   }
   
   return 0;
}