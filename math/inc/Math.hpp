#pragma once

#include "Vector2.hpp"

namespace jp::math
{
   template <typename T>
   Vector2<T> abs(const Vector2<T>& vec)
   {
      return math::Vector2<T>(std::abs(vec.x), std::abs(vec.y));
   }

   template <typename T>
   T crossProduct(const Vector2<T>& a, const Vector2<T>& b)
   {
      return a.x * b.y - b.x * a.y;
   }

   template <typename T>
   T sign(T value)
   {
      if (value == static_cast<T>(0))
      {
         return value;
      }

      return value / std::abs(value);
   }
}
