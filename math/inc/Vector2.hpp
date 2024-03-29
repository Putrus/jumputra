#pragma once

#include <iostream>

namespace jp::math
{
   template <typename T>
   struct Vector2
   {
      Vector2();
      Vector2(T value);
      Vector2(T x, T y);
      Vector2(const Vector2& other);
      virtual ~Vector2();

      T cross(const Vector2& other) const;

      Vector2 operator+(const Vector2& other) const;
      Vector2 operator-(const Vector2& other) const;
      Vector2 operator*(T num) const;
      Vector2 operator/(T num) const;

      Vector2& operator+=(const Vector2& other);
      Vector2& operator-=(const Vector2& other);
      Vector2& operator*=(T num);

      T x;
      T y;
   };

   template <typename T>
   Vector2<T>::Vector2() : x((T)0), y((T)0) {}

   template <typename T>
   Vector2<T>::Vector2(T value) : x(value), y(value) {}

   template <typename T>
   Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

   template <typename T>
   Vector2<T>::Vector2(const Vector2& other) : x(other.x), y(other.y) {}

   template <typename T>
   Vector2<T>::~Vector2() {}

   template <typename T>
   T Vector2<T>::cross(const Vector2& other) const
   {
      return x * other.y - other.x * y;
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator+(const Vector2& other) const
   {
      return { x + other.x, y + other.y };
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator-(const Vector2& other) const
   {
      return { x - other.x, y - other.y };
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator*(T num) const
   {
      return { x * num, y * num };
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator/(T num) const
   {
      return { x / num, y / num };
   }

   template <typename T>
   Vector2<T>& Vector2<T>::operator+=(const Vector2& other)
   {
      x += other.x;
      y += other.y;
      return *this;
   }

   template <typename T>
   Vector2<T>& Vector2<T>::operator-=(const Vector2& other)
   {
      x -= other.x;
      y -= other.y;
      return *this;
   }

   template <typename T>
   Vector2<T>& Vector2<T>::operator*=(T num)
   {
      x *= num;
      y *= num;
      return *this;
   }

   template <typename T>
   std::istream& operator>>(std::istream& is, Vector2<T>& vec)
   {
      is >> vec.x >> vec.y;
      return is;
   }

   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
   {
      os << vec.x << ' ' << vec.y;
      return os;
   }

   template <typename T>
   bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
   {
      return lhs.x == rhs.x && lhs.y == rhs.y;
   }

   template <typename T>
   bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
   {
      return lhs.x != rhs.x || lhs.y != rhs.y;
   }
}
