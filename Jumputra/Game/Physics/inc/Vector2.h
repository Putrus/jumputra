
namespace jp::game::physics
{
   template <typename T>
   struct Vector2
   {
      T x;
      T y;

      Vector2() : x(static_cast<T>(0)), y(static_cast<T>(0))
      {}

      Vector2(T x, T y) : x(x), y(y)
      {}

      Vector2(const Vector2& other) : x(other.x), y(other.y)
      {}

      Vector2(T value) : x(value), y(value)
      {}

      ~Vector2()
      {}

      T length()
      {
         return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
      }

      Vector2 operator+(const Vector2& other)
      {
         return Vector2(x + other.x, y + other.y);
      }

      Vector2 operator-(const Vector2& other)
      {
         return Vector2(x - other.x, y - other.y);
      }

      Vector2 operator*(T value)
      {
         return Vector2(x * value, y * value);
      }

      Vector2& operator+=(const Vector2& other)
      {
         x += other.x;
         y += other.y;
         return *this;
      }

      Vector2& operator-=(const Vector2& other)
      {
         x -= other.x;
         y -= other.y;
         return *this;
      }

      Vector2& operator*=(T value)
      {
         x *= value;
         y *= value;
         return *this;
      }
   };

   template <typename T>
   std::istream& operator>>(std::istream& is, Vector2<T>& vector)
   {
      is >> vector.x >> vector.y;
      return is;
   }

   template <typename T>
   std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector)
   {
      os << '(' << vector.x << ", " << vector.y << ')';
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