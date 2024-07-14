#include "pch.hpp"
#include "core/Logger.hpp"
#include "core/GameWindow.hpp"

using namespace engine::core;

int main()
{
	Logger::Init();

	GameWindow window = GameWindow(1366, 768, "FGE");

	return window.Run();
}