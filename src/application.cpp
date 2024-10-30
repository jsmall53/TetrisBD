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
		rCtx.ScoreViewRatio = 0.33;
		rCtx.PlayFieldRatio = 0.34;
		rCtx.PreviewRatio = 0.33;
		
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
		//DrawText("Fullscreen toggle: Alt + Enter", 10, 40, 15, LIGHTGRAY);

		int curWidth = GetScreenWidth();
		int curHeight = GetScreenHeight();
		////DrawText(TextFormat("Render size: %i x %i", GetRenderWidth(), GetRenderHeight()), 40, 200, 20, RAYWHITE);
		////DrawText(TextFormat("Screen size: %i x %i", GetScreenWidth(), GetScreenHeight()), 40, 250, 20, RAYWHITE);

		//int borderWidth = 3;

		//int menuRecOffset = 0;
		//int menuRecWidth = curWidth * 0.25;
		//int menuRecHeight = curHeight;
		//
		//int playfieldOffset = menuRecOffset + menuRecWidth + borderWidth;
		//int playfieldWidth = curWidth * 0.5 - 2;
		//int playfieldHeight = menuRecHeight;

		//int previewOffset = playfieldOffset + playfieldWidth + borderWidth;
		//int previewWidth = curWidth * 0.25 - 2;
		//int previewHeight = menuRecHeight;

		//DrawRectangle(menuRecOffset, 0, menuRecWidth, menuRecHeight, LIGHTGRAY);
		//DrawRectangle(playfieldOffset, 0, playfieldWidth, playfieldHeight, LIGHTGRAY);
		//DrawRectangle(previewOffset, 0, previewWidth, previewHeight, LIGHTGRAY);

		//DrawText(m_appSpec.Title.c_str(), 10, 10, 20, BLACK);
		m_game->OnRender();
		// m_game->RenderUI()???

		m_renderer->Update();
		DrawTextureEx(m_renderer->GetTexture(), Vector2{ 0.0f, 0.0f }, 0, (float)m_appSpec.Scale, WHITE);

		if (m_showFps)
		{
			int fpsX = (int)(curWidth * 0.92);
			int fpsY = (int)(curHeight * 0.97);
			DrawFPS(fpsX, fpsY);
			//DrawText(TextFormat("FPS Loc: (%i, %i)", fpsX, fpsY), 40, 300, 20, RAYWHITE);
		}

		EndDrawing();
	}
}