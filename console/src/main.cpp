#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"

#include "../../logic/inc/Properties.hpp"

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

   jp::logic::Properties properties;
   properties.loadFromJsonFile(propertiesFilename);

   if (algortihmName == "genetic")
   {

   }
   else if (algortihmName == "greedy")
   {

   }

   return 0;
}