#pragma once

namespace jp::logic
{
   class Selectable
   {
   public:
      virtual void deselect();
      virtual void select();

      bool isSelected() const;

   private:
      bool mSelected = false;
   };
}