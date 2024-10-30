#include "game.h"

namespace TetrisBD
{
	Game::Game()
	{
		m_playfield.Init();
	}

	void Game::OnUpdate()
	{

	}

	void Game::OnRender()
	{
		m_playfield.OnRender();
		// m_score.OnRender();
		// m_preview.OnRender();
	}
}