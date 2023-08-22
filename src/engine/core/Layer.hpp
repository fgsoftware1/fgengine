#ifndef __LAYER_H__
#define __LAYER_H__

#pragma once

#include "pch.hpp"

namespace engine
{
	namespace core
	{
		class Layer
		{
		public:
			Layer(const std::string &name = "Layer");
			virtual ~Layer();

			virtual void OnAttach();
			virtual void OnDetach();
			virtual void OnUpdate();
			// TODO: Events system
			// virtual void OnEvent(Event &event);

			const std::string &GetName() const { return m_DebugName; }

		protected:
			std::string m_DebugName;
		};
	} // namespace core
} // namespace engine

#endif // __LAYER_H__