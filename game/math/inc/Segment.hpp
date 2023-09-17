#pragma once

#include "Vector2.hpp"

namespace jp::game::math
{
    template <typename T>
    class Segment
    {
    public:
        Segment();
        Segment(T aX, T aY, T bX, T bY);
        Segment(const Vector2<T>& a, const Vector2<T>& b);

        bool isHorizontal() const;
        bool isVertical() const;
        bool isDiagonal() const;

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
    bool Segment<T>::isDiagonal() const
    {
        return std::abs(a.x - b.x) == std::abs(a.y - b.y);
    }

    template <typename T>
    void Segment<T>::swapPoints()
    {
        std::swap(a, b);
    }
}