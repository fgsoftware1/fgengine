#pragma once 

#include "Common.h"
#include "Vector3.hpp"
#include "Vector2.hpp"

namespace fgengine{
    namespace math{
        struct Rectangle;

        struct FGE_API AABB
        {
            Vector3 min;
            Vector3 max;

            AABB();
            AABB(const Rectangle& rectangle);
            AABB(const Vector2& min, const Vector2& max);
            AABB(const Vector3& min, const Vector3& max);
            AABB(float x, float y, float width, float height);
            AABB(float x, float y, float z, float width, float height, float depth);

            bool Intersects(const AABB& other) const;
            bool Contains(const Vector2& point) const;
            bool Contains(const Vector3& point) const;

            Vector3 Center() const;

            bool operator==(const AABB& other) const;
            bool operator!=(const AABB& other) const;
            bool operator<(const AABB& other) const;
            bool operator>(const AABB& other) const;

            friend std::ostream& operator<<(std::ostream& stream, const AABB& aabb);

            inline Vector3 GetSize() const { return Vector3(abs(max.x - min.x), abs(max.y - min.y), abs(max.z - min.z)); }
        } ;   
    }
}
