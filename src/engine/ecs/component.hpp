#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#pragma once

namespace engine
{
	namespace ecs
	{
		class Entity;

		class Component
		{
		public:
			virtual ~Component() = default;
			virtual void Update() {}
		};
	} // namespace ecs
} // namespace engine
#endif // __COMPONENT_H__