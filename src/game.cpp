#include "game.h"
#include "application.h"
#include <random>

namespace TetrisBD
{
	Game::Game()
	{
		m_playfield.Init();
		
		m_currentTetromino = TetrominoType::T;
		//m_currentTetromino = RandomTetromino();
		m_nextTetromino = RandomTetromino();
		m_position = GetStartingPositionState(m_currentTetromino);
		m_gravTimer.Reset();
	}

	void Game::OnUpdate()
	{
		if (m_gravTimer.ElapsedMillis() >= 200)
		{
			//MoveTetrominoDown();
			m_gravTimer.Reset();
		}

		auto key = GetKeyPressed();
		switch (key)
		{
		case KEY_LEFT:
			MoveTetrominoLeft();
			break;
		case KEY_RIGHT:
			MoveTetriminoRight();
			break;
		case KEY_UP:
			RotateTetromino();
			break;
		case KEY_DOWN:
			MoveTetrominoDown();
			break;
		default:
			break;
		}
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

	void Game::MoveTetrominoDown()
	{
		if (CanBlockMove(m_position.row + 1, m_position.col))
		{
			m_position.row++;
		}
		else 
		{
			LockTetromino();
		}
	}

	void Game::MoveTetrominoLeft()
	{
		if (CanBlockMove(m_position.row, m_position.col - 1))
		{
			m_position.col--;
		}
	}

	void Game::MoveTetriminoRight()
	{
		if (CanBlockMove(m_position.row, m_position.col + 1))
		{
			m_position.col++;
		}
	}

	void Game::RotateTetromino()
	{
		m_rotation = (m_rotation + 1) % 4;
		// TODO: double check the column position and move left or right depending on the position.
		if(!CanBlockMove(m_position.row, m_position.col))
		{
			// TODO: figure out how to shift the column position.
		}
	}

	void Game::LockTetromino()
	{
		const Tetromino& tetrInPlay = Tetrominoes::Tetrominoes[(int)m_currentTetromino][m_rotation];
		const BlockColor& colorId = tetrInPlay.GetColorId();
		for (int i = 0; i < 4; i++)
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			m_playfield.SetBlock((m_position.row + (int)offset.x), (m_position.col + (int)offset.y), colorId);
		}

		m_currentTetromino = m_nextTetromino;
		m_position = GetStartingPositionState(m_currentTetromino);
		m_rotation = 0;
		// TODO: check if the current one can fit
		m_nextTetromino = RandomTetromino();
		// TODO: clear any rows that need to be cleared.
	}

	TetrominoType Game::RandomTetromino()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		int min = (int)(TetrominoType::None) + 1;
		int max = (int)(TetrominoType::Max) - 1;
		std::uniform_int_distribution<int> dist(min, max);
		return (TetrominoType)dist(gen);
	}

	bool Game::CanBlockMove(int row, int col)
	{
		const Tetromino& tetrInPlay = Tetrominoes::Tetrominoes[(int)m_currentTetromino][m_rotation];
		for (int i = 0; i < 4; i++)
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			if (!m_playfield.IsBlockEmpty((row + (int)offset.x), (col + (int)offset.y)))
			{
				return false;
			}
		}
		return true;
	}
}