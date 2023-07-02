#include "../inc/Jumputra.h"

#include <iostream>
int main()
{
   std::cout << sizeof(sf::RectangleShape) << std::endl;
   std::cout << sizeof(sf::FloatRect) << std::endl;
   jp::Jumputra jumputra(960, 540);
   jumputra.run();
   return 0;
}