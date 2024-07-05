#pragma once

#include "../../../logic/inc/SelectionManager.hpp"

#include <gtest/gtest.h>

namespace jp::ut::logic
{
   class SelectionManagerTest : public testing::Test
   {
   protected:
      void SetUp() override
      {
         mSelectionManager = std::make_shared<jp::logic::SelectionManager>();
         mSelectionManager->addSelectable(std::make_shared<jp::logic::Selectable>());
         mSelectionManager->addSelectable(std::make_shared<jp::logic::Selectable>());
         mSelectionManager->addSelectable(std::make_shared<jp::logic::Selectable>());
         mSelectionManager->addSelectable(std::make_shared<jp::logic::Selectable>());
      }

      void TearDown() override {}

      std::shared_ptr<jp::logic::SelectionManager> mSelectionManager = nullptr;
   };
}