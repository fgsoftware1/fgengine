#pragma once

#include <math.h>

#include "tVector2.hpp"
#include "utils/Types.h"
#include "Constants.h"
#include "Common.h"

namespace fgengine
{
    namespace math
    {
        typedef tVector2<i32> ivec2;
        typedef tVector2<uint> uvec2;

        FGE_API inline float toRadians(float degrees)
        {
            return (float)(degrees * (PI / 180.0f));
        }

        FGE_API inline float toDegrees(float radians)
        {
            return (float)(radians * (180.0f / PI));
        }

        FGE_API inline i32 sign(float value)
        {
            return (value > 0) - (value < 0);
        }

        FGE_API inline float sin(float angle)
        {
            return ::sin(angle);
        }

        FGE_API inline float cos(float angle)
        {
            return ::cos(angle);
        }

        FGE_API inline float tan(float angle)
        {
            return ::tan(angle);
        }

        FGE_API inline float sqrt(float value)
        {
            return ::sqrt(value);
        }

        FGE_API inline float rsqrt(float value)
        {
            return 1.0f / ::sqrt(value);
        }

        FGE_API inline float asin(float value)
        {
            return ::asin(value);
        }

        FGE_API inline float acos(float value)
        {
            return ::acos(value);
        }

        FGE_API inline float atan(float value)
        {
            return ::atan(value);
        }

        FGE_API inline float atan2(float y, float x)
        {
            return ::atan2(y, x);
        }

        FGE_API inline float _min(float value, float minimum)
        {
            return (value < minimum) ? minimum : value;
        }

        FGE_API inline float _max(float value, float maximum)
        {
            return (value > maximum) ? maximum : value;
        }

        FGE_API inline float clamp(float value, float minimum, float maximum)
        {
            return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
        }
    }
}