#pragma once
#pragma warning (disable:4251)

#ifdef FGE_PLATFORM_WINDOWS
#ifdef FGE_CORE_DLL
#define FGE_API __declFGEec(dllexport)
#else
#define FGE_API __declFGEec(dllimport)
#endif
#else
#define FGE_API
#endif

#define BIT(x) (1 << x)

#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define METHOD(x) METHOD_1(x)

#ifdef FGE_DEBUG
#define FGE_DEBUG_METHOD_V(x) x;
#else
#define FGE_DEBUG_METHOD_V(x) x {}
#endif