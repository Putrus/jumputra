#pragma once

#include "../../core/inc/Jsonable.hpp"

#include "Math.hpp"

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

      bool intersects(const Segment& other) const;

      bool isDiagonal() const;
      bool isHorizontal() const;
      bool isVertical() const;

      T getIntercept() const;
      T getSlope() const;

      void swapPoints();

      Segment& operator=(const nlohmann::json& json);

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
      json["a"] = a.toJson();
      json["b"] = b.toJson();
      return json;
   }

   template <typename T>
   bool Segment<T>::intersects(const Segment& other) const
   {
      const Vector2<T>& c = other.a;
      const Vector2<T>& d = other.b;

      Vector2<T> ab = Vector2<T>(b.x - a.x, b.y - a.y);
      Vector2<T> ac = Vector2<T>(c.x - a.x, c.y - a.y);
      Vector2<T> ad = Vector2<T>(d.x - a.x, d.y - a.y);

      Vector2<T> cd = Vector2<T>(d.x - c.x, d.y - c.y);
      Vector2<T> ca = Vector2<T>(a.x - c.x, a.y - c.y);
      Vector2<T> cb = Vector2<T>(b.x - c.x, b.y - c.y);

      T abacCrossProduct = crossProduct(ab, ac);
      T abadCrossProduct = crossProduct(ab, ad);
      T cdcaCrossProduct = crossProduct(cd, ca);
      T cdcbCrossProduct = crossProduct(cd, cb);

      if (((abacCrossProduct < static_cast<T>(0) && abadCrossProduct > static_cast<T>(0)) ||
         (abacCrossProduct > static_cast<T>(0) && abadCrossProduct < static_cast<T>(0))) &&
         ((cdcaCrossProduct < static_cast<T>(0) && cdcbCrossProduct > static_cast<T>(0)) ||
         (cdcaCrossProduct > static_cast<T>(0) && cdcbCrossProduct < static_cast<T>(0))))
      {
         return true;
      }

      auto checkOverlapping = [](const Vector2<T> &a, const Vector2<T> &b, const Vector2<T> &c) -> bool
         {
            return std::min(a.x, b.x) <= c.x && c.x <= std::max(a.x, b.x) &&
               std::min(a.y, b.y) <= c.y && c.y <= std::max(a.y, b.y);
         };

      if ((abacCrossProduct == static_cast<T>(0) && checkOverlapping(a, b, c)) ||
         (abadCrossProduct == static_cast<T>(0) && checkOverlapping(a, b, d)) ||
         (cdcaCrossProduct == static_cast<T>(0) && checkOverlapping(c, d, a)) ||
         (cdcbCrossProduct == static_cast<T>(0) && checkOverlapping(c, d, b)))
      {
         return true;
      }

      return false;
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
   Segment<T>& Segment<T>::operator=(const nlohmann::json& json)
   {
      fromJson(json);
      return *this;
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
