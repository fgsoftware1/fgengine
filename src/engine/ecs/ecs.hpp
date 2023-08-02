#ifndef __ECS_H__
#define __ECS_H__

#pragma once

#include "pch.hpp"
#include "entity.hpp"

namespace engine
{
	namespace ecs
	{
		class ECS
		{
		public:
			ECS();
			~ECS();

			Entity CreateEntity();
			void DestroyEntity(Entity entity);

			void Update();

		private:
			uint32_t m_LastEntityID;
			std::vector<std::shared_ptr<Entity>> m_Entities;
		};
	} // namespace ecs
} // namespace engine
#endif // __ECS_H__