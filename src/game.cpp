#include "game.h"
#include "application.h"

namespace TetrisBD
{
	Game::Game()
	{
		m_playfield.Init();
		
		// TODO: get a random block
		m_currentTetromino = TetrominoType::O;
		m_position = GetStartingPositionState(m_currentTetromino);
	}

	void Game::OnUpdate()
	{
	}

	void Game::OnRender()
	{
		m_playfield.OnRender();

		Renderer* pRenderer = Application::GetRenderer();

		const Tetromino& tetrInPlay = Tetrominoes::Tetrominoes[(int)m_currentTetromino][m_rotation];
		for (int i = 0; i < 4; i++) // render the 4 blocks
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			Block anchor = m_playfield.GetBlock((m_position.row + (int)offset.x), (m_position.col + (int)offset.y));
			anchor.colorId = tetrInPlay.GetColorId();
			pRenderer->RenderBlock(anchor);
		}
		// m_score.OnRender();
		// m_preview.OnRender();
	}

	PositionState Game::GetStartingPositionState(TetrominoType type)
	{
		switch (type)
		{
		case TetrominoType::I:
			return { -1, 3 };
		case TetrominoType::O:
			return { 0, 4 };
		case TetrominoType::T:
		case TetrominoType::S:
		case TetrominoType::Z:
		case TetrominoType::J:
		case TetrominoType::L:
			return { 0, 3 };
		default: // ::None
			return { 0, 0 };
		}
	}
}