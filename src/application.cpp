#include "raylib.h"

#include "Application.h"


namespace TetrisBD
{
	static Application* s_Instance = nullptr;

	Application::Application(const AppSpec& appSpec)
		:m_appSpec(appSpec), m_showFps(false)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}


	void Application::Run()
	{
		int width = m_appSpec.Width * m_appSpec.Scale;
		int height = m_appSpec.Height * m_appSpec.Scale;

		InitWindow(width, height, m_appSpec.Title.c_str());
		SetExitKey(0);

		//Image icon = LoadImage("path");
		//SetWindowIcon(icon);

		SetTargetFPS(60);

		RendererContext rCtx;
		rCtx.Width = m_appSpec.Width;
		rCtx.Height = m_appSpec.Height;
		rCtx.BorderWidth = 3;
		rCtx.ScoreViewRatio = 0.33f;
		rCtx.PlayFieldRatio = 0.34f;
		rCtx.PreviewRatio = 0.33f;
		
		m_renderer = std::make_shared<Renderer>(rCtx);
		m_game = std::make_unique<Game>();

		while (!WindowShouldClose())
		{
			OnUpdate();
			OnRender();
		}

		CloseWindow();
		// UnloadImage(icon);
	}

	void Application::OnUpdate()
	{
		m_game->OnUpdate();

		if (IsKeyPressed(KEY_R) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))
		{
			m_showFps = !m_showFps;
		}
	}

	void Application::OnRender()
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		//=======================================
		int curWidth = GetScreenWidth();
		int curHeight = GetScreenHeight();

		m_game->OnRender();
		// m_game->RenderUI()???

		m_renderer->Update();
		DrawTextureEx(m_renderer->GetTexture(), Vector2{ 0.0f, 0.0f }, 0, (float)m_appSpec.Scale, WHITE);

		if (m_showFps)
		{
			int fpsX = (int)(curWidth * 0.92);
			int fpsY = (int)(curHeight * 0.97);
			DrawFPS(fpsX, fpsY);
		}

		EndDrawing();
	}
}