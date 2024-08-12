#include "../inc/Consolutra.hpp"

#include <iostream>

int main(int argc, char** argv)
{
   if (argc != 4)
   {
      std::cerr << "Wrong arguments number. Should be " << argv[0] << " <properties filename> <world filename> <algorithm name>" << std::endl;
      return -1;
   }

   std::string propertiesFilename = argv[1];
   std::string worldFilename = argv[2];
   std::string algortihmName = argv[3];

   try
   {
      jp::console::Consolutra consolutra(propertiesFilename, worldFilename, algortihmName);
      consolutra.run();
   }
   catch (const std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }
   
   return 0;
}