#include "ScriptComponent.hpp"
#include "Logger.hpp"

namespace engine
{
	namespace ecs
	{
		ScriptComponent::ScriptComponent(const std::string &scriptPath) : m_ScriptPath(scriptPath) {}

		ScriptComponent::~ScriptComponent() {}

		void ScriptComponent::Update()
		{
			engine::core::Logger::Debug(engine::core::LogChannel::Scripting, "Running script from: " + m_ScriptPath);
		}
	} // namespace ecs
} // namespace engine
