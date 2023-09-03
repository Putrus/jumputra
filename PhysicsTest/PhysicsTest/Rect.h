#pragma once

#include "Vector2.h"

namespace jp::math
{
   template <typename T>
   class Rect
   {
   public:
      Rect();
      Rect(T left, T top, T width, T height);
      Rect(const Vector2<T>& position, const Vector2<T>& size);
      Rect(const Rect& other);

      Vector2<T> getPosition() const;
      Vector2<T> getSize() const;
      Vector2<T> getLeftTop() const;
      Vector2<T> getLeftBottom() const;
      Vector2<T> getRightTop() const;
      Vector2<T> getRightBottom() const;
      Vector2<T> getCenter() const;

      T getRight() const;
      T getBottom() const;

      Rect operator+(const Vector2<T>& vec) const;

      Rect& operator+=(const Vector2<T>& vec);

      T left;
      T top;
      T width;
      T height;
   };

   template <typename T>
   Rect<T>::Rect() : left((T)0), top((T)0), width((T)0), height((T)0) {}

   template <typename T>
   Rect<T>::Rect(T left, T top, T width, T height) : left(left), top(top), width(width), height(height) {}

   template <typename T>
   Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) : Rect(position.x, position.y, size.x, size.y) {}

   template <typename T>
   Rect<T>::Rect(const Rect& other) : left(other.left), top(other.top), width(other.width), height(other.height) {}

   template <typename T>
   Vector2<T> Rect<T>::getPosition() const
   {
      return { left, top };
   }

   template <typename T>
   Vector2<T> Rect<T>::getSize() const
   {
      return { width, height };
   }

   template <typename T>
   Vector2<T> Rect<T>::getLeftTop() const
   {
      return { left, top };
   }

   template <typename T>
   Vector2<T> Rect<T>::getLeftBottom() const
   {
      return { left, getBottom()};
   }

   template <typename T>
   Vector2<T> Rect<T>::getRightTop() const
   {
      return { getRight(), top };
   }

   template <typename T>
   Vector2<T> Rect<T>::getRightBottom() const
   {
      return { getRight(), getBottom() };
   }

   template <typename T>
   T Rect<T>::getRight() const
   {
      return left + width;
   }

   template <typename T>
   T Rect<T>::getBottom() const
   {
      return top + height;
   }

   template <typename T>
   Vector2<T> Rect<T>::getCenter() const
   {
      return { (left + getRight()) / (T)2, (top + getBottom()) / (T)2 };
   }

   template <typename T>
   Rect<T> Rect<T>::operator+(const Vector2<T>& vec) const
   {
      return { left + vec.x, top + vec.y, width, height };
   }

   template <typename T>
   Rect<T>& Rect<T>::operator+=(const Vector2<T>& vec)
   {
      left += vec.x;
      top += vec.y;
      return *this;
   }
}