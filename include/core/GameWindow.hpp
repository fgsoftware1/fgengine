#pragma once

#include "pch.hpp"
#include "core/Window.hpp"

namespace engine {
	namespace core {
		class GameWindow : public Window {
		public:
			GameWindow(int width, int height, std::string title) : Window(width, height, title) {}

			void Init() override;
			void Load() override;
			void Update() override;
			void Render() override;
			void Unload() override;
			void Shutdown() override;
		};
	}
}