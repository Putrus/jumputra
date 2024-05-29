#include "../inc/SelectionManager.hpp"

namespace jp::logic
{
   void SelectionManager::addSelectable(const std::shared_ptr<Selectable> &selectable)
   {
      mSelectables.push_back(selectable);
   }
      
   int SelectionManager::getSelected() const
   {
      return mSelected;
   }

   void SelectionManager::setSelected(int selected)
   {
      if (mSelectables.empty())
      {
         return;
      }
      
      if (selected < 0)
      {
         selected = static_cast<int>(mSelectables.size()) - 1;
      }
      else
      {
         selected %= mSelectables.size();
      }

      mSelectables[mSelected]->deselect();
      mSelected = selected;
      mSelectables[mSelected]->select();
   }
}