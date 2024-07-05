#include "../inc/SelectionManagerTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST_F(SelectionManagerTest, SetSelectedPlus)
   {
      mSelectionManager->setSelected(1);

      EXPECT_EQ(1, mSelectionManager->getSelected());
   }

   TEST_F(SelectionManagerTest, SetSelectedMinus)
   {
      mSelectionManager->setSelected(-1);

      EXPECT_EQ(3, mSelectionManager->getSelected());
   }

   TEST_F(SelectionManagerTest, SetSelectedGreaterThanSize)
   {
      mSelectionManager->setSelected(6);

      EXPECT_EQ(2, mSelectionManager->getSelected());
   }

   TEST_F(SelectionManagerTest, SetSelectedEmpty)
   {
      mSelectionManager = std::make_shared<SelectionManager>();
      mSelectionManager->setSelected(2);

      EXPECT_EQ(0, mSelectionManager->getSelected());
   }
}