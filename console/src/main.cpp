#include "../inc/Consolutra.hpp"

#include <iostream>

int main(int argc, char** argv)
{
   if (argc != 5)
   {
      std::cerr << "Wrong arguments number. Should be " << argv[0] << " <action> <properties filename> <world filename> <algorithm name>" << std::endl;
      return -1;
   }

   std::string action = argv[1];
   std::string propertiesFilename = argv[2];
   std::string worldFilename = argv[3];
   std::string algortihmName = argv[4];

   if (action == "-run")
   {
      try
      {
         jp::console::Consolutra consolutra(propertiesFilename, worldFilename, algortihmName);
         consolutra.run();
      }
      catch (const std::exception& e)
      {
         std::cerr << e.what() << std::endl;
      }
   }
   else if (action == "-investigate")
   {
      try
      {
         jp::console::Consolutra consolutra(propertiesFilename, worldFilename, algortihmName);
         consolutra.investigate();
      }
      catch (const std::exception& e)
      {
         std::cerr << e.what() << std::endl;
      }
   }
   else
   {
      std::cerr << "Wrong action name. Possible actions: -run, -investigate" << std::endl;
      return -1;
   }
   
   return 0;
}