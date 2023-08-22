#pragma once

#include "Rect.h"

namespace jp::math
{
   template <typename T>
   class Segment
   {
   public:
      Segment();
      Segment(T aX, T aY, T bX, T bY);
      Segment(const Vector2<T>& a, const Vector2<T>& b);

      bool intersects(const Segment& other) const;

      Vector2<T> a;
      Vector2<T> b;
   };

   template <typename T>
   Segment<T>::Segment() : a((T)0, (T)0), b((T)0, (T)0) {}

   template <typename T>
   Segment<T>::Segment(T aX, T aY, T bX, T bY) : a(aX, aY), b(bX, bY) {}

   template <typename T>
   Segment<T>::Segment(const Vector2<T>& p1, const Vector2<T>& p2) : p1(p1), p2(p2) {}

   template <typename T>
   bool Segment<T>::intersects(const Segment& other) const
   {
      //to better visualisation
      float c = other.a;
      float d = other.b;

      //calculate all direction vectors
      //current segment
      jp::math::Vector2<float> dirAB = b - a;
      jp::math::Vector2<float> dirAC = c - a;
      jp::math::Vector2<float> dirAD = d - a;
      //other segment
      jp::math::Vector2<float> dirCD = d - c;
      jp::math::Vector2<float> dirCA = a - c;
      jp::math::Vector2<float> dirCB = b - c;

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