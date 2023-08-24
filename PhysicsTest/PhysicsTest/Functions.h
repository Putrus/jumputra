#pragma once

#include "Vector2.h"

namespace jp::math
{
   template<typename T>
   bool segmentsIntersect(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c, const Vector2<T>& d)
   {
      //calculate all direction vectors
      //first segment
      jp::math::Vector2<float> dirAB = b - a;
      jp::math::Vector2<float> dirAC = c - a;
      jp::math::Vector2<float> dirAD = d - a;

      //second segment
      jp::math::Vector2<float> dirCD = d - c;
      jp::math::Vector2<float> dirCA = a - c;
      jp::math::Vector2<float> dirCB = b - c;

      //cross products
      float crossA = dirCD.cross(dirCA);
      float crossB = dirCD.cross(dirCB);
      float crossC = dirAB.cross(dirAC);
      float crossD = dirAB.cross(dirAD);

      //if the cross products have opposite signs, then the segments intersect
      if (((crossA < 0 && crossB > 0) || (crossA > 0 && crossB < 0)) &&
         ((crossC < 0 && crossD > 0) || (crossC > 0 && crossD < 0)))
      {
         return true;
      }

      //here it could be checking if the end of a segment intersects another, but it's not needed
      return false;
   }
}