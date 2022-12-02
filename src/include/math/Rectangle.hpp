#pragma once

#include "Common.h"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace fgengine{
    namespace math{
        struct AABB;

        struct FGE_API Rectangle
        {
            union
            {
                Vector2 position;
                struct
                {
                    float x;
                    float y;
                };
            };
            union
            {
                Vector2 size;
                struct
                {
                    float width;
                    float height;
                };
            };

            Rectangle();
            ~Rectangle();
            Rectangle(const AABB& aabb);
            Rectangle(const Vector2& position, const Vector2& size);
            Rectangle(float x, float y, float width, float height);

            bool Intersects(const Rectangle& other) const;
            bool Contains(const Vector2& point) const;
            bool Contains(const Vector3& point) const;

            inline Vector2 GetMinimumBound() const { return position - size; }
            inline Vector2 GetMaximumBound() const { return position + size; }

            bool operator==(const Rectangle& other) const;
            bool operator!=(const Rectangle& other) const;

            bool operator<(const Rectangle& other) const;
            bool operator>(const Rectangle& other) const;

            friend std::ostream& operator<<(std::ostream& stream, const Rectangle& Rectangle);
        };
    }
}