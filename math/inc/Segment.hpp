#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "Vector2.hpp"

namespace jp::math
{
   template <typename T>
   class Segment : public core::Jsonable
   {
   public:
      Segment();
      Segment(T aX, T aY, T bX, T bY);
      Segment(const Vector2<T>& a, const Vector2<T>& b);
      Segment(const nlohmann::json& json);
      Segment(const Segment& other);

      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      bool isDiagonal() const;
      bool isHorizontal() const;
      bool isVertical() const;
      
      T getIntercept() const;
      T getSlope() const;

      void swapPoints();

      Vector2<T> a;
      Vector2<T> b;
   };

   template <typename T>
   Segment<T>::Segment() : a((T)0, (T)0), b((T)0, (T)0) {}

   template <typename T>
   Segment<T>::Segment(T aX, T aY, T bX, T bY) : a(aX, aY), b(bX, bY) {}

   template <typename T>
   Segment<T>::Segment(const Vector2<T>& a, const Vector2<T>& b) : a(a), b(b) {}

   template <typename T>
   Segment<T>::Segment(const nlohmann::json& json)
   {
      fromJson(json);
   }

   template <typename T>
   Segment<T>::Segment(const Segment& other) : a(other.a), b(other.b) {}

   template <typename T>
   void Segment<T>::fromJson(const nlohmann::json& json)
   {
      a = json.at("a");
      b = json.at("b");
   }

   template <typename T>
   nlohmann::json Segment<T>::toJson() const
   {
      nlohmann::json json;
      json.at("a") = a.toJson();
      json.at("b") = b.toJson();
      return json;
   }

   template <typename T>
   bool Segment<T>::isDiagonal() const
   {
      return std::abs(a.x - b.x) == std::abs(a.y - b.y);
   }

   template <typename T>
   bool Segment<T>::isHorizontal() const
   {
      return a.y == b.y;
   }

   template <typename T>
   bool Segment<T>::isVertical() const
   {
      return a.x == b.x;
   }

   template <typename T>
   T Segment<T>::getIntercept() const
   {
      return b.y - getSlope() * b.x;
   }

   template <typename T>
   T Segment<T>::getSlope() const
   {
      T diffX = (b.x - a.x);
      if (diffX == (T)0)
      {
         throw std::runtime_error("jp::math::Segment<T>::getSlope - Failed to get the slope of the segment, the denominator is 0");
      }
      else
      {
         return (b.y - a.y) / diffX;
      }
   }

   template <typename T>
   void Segment<T>::swapPoints()
   {
      std::swap(a, b);
   }

   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Segment<T>& segment)
   {
      os << segment.a << " -> " << segment.b;
      return os;
   }

   template <typename T>
   bool operator==(const Segment<T>& lhs, const Segment<T>& rhs)
   {
      return lhs.a == rhs.a && lhs.a == rhs.a;
   }
}
