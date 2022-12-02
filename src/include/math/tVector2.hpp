#pragma once

#include <ostream>

#include "Common.h"

namespace fgengine
{
    namespace math
    {
        template <class T>
        struct FGE_API tVector2
        {
            T x, y;

            tVector2<T>();
            tVector2<T>(const T &x, const T &y);

            tVector2<T> &Add(const tVector2<T> &other);
            tVector2<T> &Subtract(const tVector2<T> &other);
            tVector2<T> &Multiply(const tVector2<T> &other);
            tVector2<T> &Divide(const tVector2<T> &other);

            friend tVector2<T> operator+(tVector2<T> left, const tVector2<T> &right);
            friend tVector2<T> operator-(tVector2<T> left, const tVector2<T> &right);
            friend tVector2<T> operator*(tVector2<T> left, const tVector2<T> &right);
            friend tVector2<T> operator/(tVector2<T> left, const tVector2<T> &right);

            bool operator==(const tVector2<T> &other);
            bool operator!=(const tVector2<T> &other);

            tVector2<T> &operator+=(const tVector2<T> &other);
            tVector2<T> &operator-=(const tVector2<T> &other);
            tVector2<T> &operator*=(const tVector2<T> &other);
            tVector2<T> &operator/=(const tVector2<T> &other);

            friend std::ostream &operator<<(std::ostream &stream, const tVector2 &vector);
        };

        template <class T>
        tVector2<T>::tVector2()
        {
            x = 0;
            y = 0;
        }

        template <class T>
        tVector2<T>::tVector2(const T &x, const T &y)
        {
            this->x = x;
            this->y = y;
        }

        template <class T>
        tVector2<T> &tVector2<T>::Add(const tVector2<T> &other)
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        template <class T>
        tVector2<T> &tVector2<T>::Subtract(const tVector2<T> &other)
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        template <class T>
        tVector2<T> &tVector2<T>::Multiply(const tVector2<T> &other)
        {
            x *= other.x;
            y *= other.y;

            return *this;
        }

        template <class T>
        tVector2<T> &tVector2<T>::Divide(const tVector2<T> &other)
        {
            x /= other.x;
            y /= other.y;

            return *this;
        }

        template <class T>
        tVector2<T> operator+(tVector2<T> left, const tVector2<T> &right)
        {
            return left.Add(right);
        }

        template <class T>
        tVector2<T> operator-(tVector2<T> left, const tVector2<T> &right)
        {
            return left.Subtract(right);
        }

        template <class T>
        tVector2<T> operator*(tVector2<T> left, const tVector2<T> &right)
        {
            return left.Multiply(right);
        }

        template <class T>
        tVector2<T> operator/(tVector2<T> left, const tVector2<T> &right)
        {
            return left.Divide(right);
        }

        template <class T>
        tVector2<T> &tVector2<T>::operator+=(const tVector2<T> &other)
        {
            return Add(other);
        }

        template <class T>
        tVector2<T> &tVector2<T>::operator-=(const tVector2<T> &other)
        {
            return Subtract(other);
        }

        template <class T>
        tVector2<T> &tVector2<T>::operator*=(const tVector2<T> &other)
        {
            return Multiply(other);
        }

        template <class T>
        tVector2<T> &tVector2<T>::operator/=(const tVector2<T> &other)
        {
            return Divide(other);
        }

        template <class T>
        bool tVector2<T>::operator==(const tVector2<T> &other)
        {
            return x == other.x && y == other.y;
        }

        template <class T>
        bool tVector2<T>::operator!=(const tVector2<T> &other)
        {
            return !(*this == other);
        }

        template <class T>
        std::ostream &operator<<(std::ostream &stream, const tVector2<T> &vector)
        {
            stream << "tVector2: (" << vector.x << ", " << vector.y << ")";
            return stream;
        }
    }
}