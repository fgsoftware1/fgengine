#include "RendererAPI.hpp"
#include "Logger.hpp"
#include "utils.hpp"
#include "OpenGLRendererAPI.hpp"

using engine::core::Logger;
using engine::core::LogChannel;

namespace engine
{
	namespace renderer
	{
		RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

		Scope<RendererAPI> RendererAPI::Create()
		{
			switch (s_API)
			{
			case RendererAPI::API::None:
				Logger::Error(LogChannel::App, "RendererAPI None not currently supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
			}

			Logger::Error(LogChannel::App, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}