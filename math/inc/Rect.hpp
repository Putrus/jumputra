#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "Vector2.hpp"

namespace jp::math
{
   template <typename T>
   struct Rect : public core::Jsonable
   {
      Rect();
      Rect(T left, T top, T width, T height);
      Rect(const Vector2<T>& position, const Vector2<T>& size);
      Rect(const nlohmann::json& json);
      Rect(const Rect& other);

      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      bool intersects(const Rect& other) const;

      Vector2<T> getPosition() const;
      Vector2<T> getSize() const;
      Vector2<T> getLeftTop() const;
      Vector2<T> getLeftBottom() const;
      Vector2<T> getRightTop() const;
      Vector2<T> getRightBottom() const;
      Vector2<T> getCenter() const;
      T getRight() const;
      T getBottom() const;

      void setPosition(T x, T y);
      void setPosition(const Vector2<T>& position);

      Rect operator+(const Vector2<T>& vec) const;

      Rect& operator=(const nlohmann::json& json);
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
   Rect<T>::Rect(const nlohmann::json& json)
   {
      fromJson(json);
   }

   template <typename T>
   Rect<T>::Rect(const Rect& other) : left(other.left), top(other.top), width(other.width), height(other.height) {}

   template <typename T>
   void Rect<T>::fromJson(const nlohmann::json& json)
   {
      left = json.at("left");
      top = json.at("top");
      width = json.at("width");
      height = json.at("height");
   }

   template <typename T>
   nlohmann::json Rect<T>::toJson() const
   {
      nlohmann::json json;
      json.at("left") = left;
      json.at("top") = top;
      json.at("width") = width;
      json.at("height") = height;
      return json;
   }

   template <typename T>
   bool Rect<T>::intersects(const Rect& other) const
   {
      Rect intersection(std::max(left, other.left),
         std::max(top, other.top), std::min(getRight(), other.getRight()),
         std::min(this->getBottom(), other.getBottom()));

      //in this case .width is .right and .height is .bottom
      if (intersection.left <= intersection.width && intersection.top <= intersection.height)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

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
   void Rect<T>::setPosition(T x, T y)
   {
      left = x;
      top = y;
   }

   template <typename T>
   void Rect<T>::setPosition(const Vector2<T>& position)
   {
      left = position.x;
      top = position.y;
   }

   template <typename T>
   Rect<T> Rect<T>::operator+(const Vector2<T>& vec) const
   {
      return { left + vec.x, top + vec.y, width, height };
   }

   template <typename T>
   Rect<T>& Rect<T>::operator=(const nlohmann::json& json)
   {
      left = json.at("left");
      top = json.at("top");
      width = json.at("width");
      height = json.at("height");
      return *this;
   }

   template <typename T>
   Rect<T>& Rect<T>::operator+=(const Vector2<T>& vec)
   {
      left += vec.x;
      top += vec.y;
      return *this;
   }

   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Rect<T>& rect)
   {
      os << rect.left << ' ' << rect.top << ' ' << rect.width << ' ' << rect.height;
      return os;
   }

   template <typename T>
   bool operator==(const Rect<T>& lhs, const Rect<T>& rhs)
   {
      return lhs.left == rhs.left && lhs.top == rhs.top &&
         lhs.width == rhs.width && lhs.height == rhs.height;
   }
}
