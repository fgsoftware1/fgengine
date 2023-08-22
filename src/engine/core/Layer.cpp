#include "Layer.hpp"

namespace engine
{
	namespace core
	{
		Layer::Layer(const std::string &name) : m_DebugName(name){}

		Layer::~Layer(){}

		void Layer::OnAttach(){}

		void Layer::OnDetach(){}

		void Layer::OnUpdate(){}

		//TODO: Event system
		//void Layer::OnEvent(Event &event){}
	} // namespace core
} // namespace engine
