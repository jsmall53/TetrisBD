#pragma once

#include <string>
#include <memory>

#include "renderer.h"
#include "game.h"

namespace TetrisBD
{
	struct AppSpec
	{
		int Width = 500;
		int Height = Width / 16 * 10;
		int Scale = 3;
		std::string Title = "TetrisBD";
	};

	class Application
	{
	public:
		Application(const AppSpec& spec = AppSpec());
		~Application();

		void Run();
		void OnRender();
		void OnUpdate();
	public:
		static Application& Get();
		static Renderer* GetRenderer() { return Get().m_renderer.get(); };
	private:

		AppSpec m_appSpec;

		std::shared_ptr<Renderer> m_renderer;
		std::unique_ptr<Game> m_game;

		bool m_showFps;
	};

}