#pragma once

#include "Selectable.hpp"

#include <memory>
#include <vector>

namespace jp::logic
{
   class SelectionManager
   {
   public:
      void addSelectable(const std::shared_ptr<Selectable> &selectable);
      
      int getSelected() const;

      void setSelected(int selected);

   protected:
      std::vector<std::shared_ptr<Selectable>> mSelectables;

   private:
      int mSelected = 0;
   };
}