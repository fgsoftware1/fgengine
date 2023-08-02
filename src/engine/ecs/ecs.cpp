#include "ecs.hpp"
#include "ScriptComponent.hpp"

namespace engine
{
	namespace ecs
	{
		ECS::ECS() : m_LastEntityID(0) {}

		ECS::~ECS() {}

		Entity ECS::CreateEntity()
		{
			uint32_t id = ++m_LastEntityID;
			auto entity = std::make_shared<Entity>(id);
			m_Entities.push_back(entity);
			return *entity;
		}

		void ECS::DestroyEntity(Entity entity)
		{
			for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
			{
				if ((*it)->GetID() == entity.GetID())
				{
					m_Entities.erase(it);
					break;
				}
			}
		}

		void ECS::Update()
		{
			for (const auto &entity : m_Entities)
			{
				auto scriptComponent = entity->GetComponent<ScriptComponent>();
				if (scriptComponent)
				{
					scriptComponent->Update();
				}
			}
		}
	} // namespace ecs
} // namespace engine
