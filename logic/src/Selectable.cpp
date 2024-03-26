#include "../inc/Selectable.hpp"

namespace jp::logic
{
   void Selectable::deselect()
   {
      mSelected = false;
   }

   void Selectable::select()
   {
      mSelected = true;
   }

   bool Selectable::isSelected() const
   {
      return mSelected;
   }
}