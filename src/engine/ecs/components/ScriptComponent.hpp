#ifndef __SCRIPTCOMPONENT_H__
#define __SCRIPTCOMPONENT_H__

#pragma once

#include "pch.hpp"
#include "component.hpp"

namespace engine
{
	namespace ecs
	{
		class ScriptComponent : public Component
		{
		public:
			ScriptComponent(const std::string &scriptPath);
			~ScriptComponent() override;

			void Update() override;
			const std::string &GetScriptPath() const { return m_ScriptPath; }

		private:
			std::string m_ScriptPath;
		};
	} // namespace ecs
} // namespace engine

#endif // __SCRIPTCOMPONENT_H__