#include "../../../logic/inc/Selectable.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST(SelectableTest, Select)
   {
      Selectable selectable;

      selectable.select();

      EXPECT_TRUE(selectable.isSelected());
   }

   TEST(SelectableTest, Deselect)
   {
      Selectable selectable;

      selectable.deselect();

      EXPECT_FALSE(selectable.isSelected());
   }
}