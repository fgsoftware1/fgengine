#ifndef __ENTITY_H__
#define __ENTITY_H__

#pragma once

#include "pch.hpp"
#include "component.hpp"

namespace engine
{
	namespace ecs
	{
		class Entity
		{
		public:
			Entity(uint32_t id);

			uint32_t GetID() const { return m_ID; }

			template <typename T>
			void AddComponent(std::shared_ptr<T> component);

			template <typename T>
			std::shared_ptr<T> GetComponent();

		private:
			uint32_t m_ID;
			std::unordered_map<size_t, std::shared_ptr<Component>> m_Components;
		};

		template <typename T>
		void Entity::AddComponent(std::shared_ptr<T> component)
		{
			size_t typeId = typeid(T).hash_code();
			m_Components[typeId] = component;
		}

		template <typename T>
		std::shared_ptr<T> Entity::GetComponent()
		{
			size_t typeId = typeid(T).hash_code();
			auto it = m_Components.find(typeId);
			if (it != m_Components.end())
			{
				return std::dynamic_pointer_cast<T>(it->second);
			}
			return nullptr;
		}
	} // namespace ecs
} // namespace engine

#endif // __ENTITY_H__