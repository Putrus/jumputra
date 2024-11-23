#include "../inc/Consolutra.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
   if (argc != 6 && argc != 9)
   {
      std::cerr << "Wrong arguments number. Is " << argc << " should be 6 or 9: " << argv[0] <<
         " <action> <properties filename> <world filename> <algorithm name> <max execution minutes> <min bots> <max bots> <step bots>" << std::endl;
      return -1;
   }

   std::string action = argv[1];
   std::string propertiesFilename = argv[2];
   std::string worldFilename = argv[3];
   std::string algortihmName = argv[4];
   std::string strMaxExecutionMinutes = argv[5];

   int maxExecutionMinutes = std::stoi(strMaxExecutionMinutes);
   int minBots = 0;
   int maxBots = 0;
   int stepBots = 0;
   if (argc == 9)
   {
      std::string strMinBots = argv[6];
      std::string strMaxBots = argv[7];
      std::string strStepBots = argv[8];
      minBots = std::stoi(strMinBots);
      maxBots = std::stoi(strMaxBots);
      stepBots = std::stoi(strStepBots);
   }

   std::cout << maxExecutionMinutes << std::endl
             << std::endl;

   if (action == "-run")
   {
      try
      {
         jp::console::Consolutra consolutra(propertiesFilename, worldFilename, algortihmName, maxExecutionMinutes, minBots, maxBots, stepBots);
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
         jp::console::Consolutra consolutra(propertiesFilename, worldFilename, algortihmName, maxExecutionMinutes, minBots, maxBots, stepBots);
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