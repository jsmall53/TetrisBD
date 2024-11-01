#include "game.h"
#include "application.h"

namespace TetrisBD
{
	Game::Game()
	{
		
		Reset();
	}

	void Game::OnUpdate()
	{
		if (m_gameOver)
		{
			if (IsKeyPressed(KEY_SPACE))
				Reset();
			return;
		}

		if (m_gravTimer.ElapsedMillis() >= 500)
		{
			MoveTetrominoDown();
			m_gravTimer.Reset();
		}
		if (IsKeyPressed(KEY_UP))
			RotateTetromino();
		else if (m_inputTimer.ElapsedMillis() >= 85)
		{
			m_inputTimer.Reset();
			if (IsKeyDown(KEY_LEFT))
				MoveTetrominoLeft();
			else if (IsKeyDown(KEY_RIGHT))
				MoveTetriminoRight();
			else if (IsKeyDown(KEY_DOWN))
				MoveTetrominoDown();
			/*auto key = GetKeyPressed();
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
			}*/
		}
	}

	void Game::OnRender()
	{
		m_playfield.OnRender();

		Renderer* pRenderer = Application::GetRenderer();

		RenderCurrentTetromino(pRenderer);
		RenderNextTetromino(pRenderer);

		if (m_gameOver)
		{
			//TODO: render a game over menu thing with a play again button or key press
			pRenderer->RenderText("Game Over!", 200, 150);
		}

		// m_score.OnRender();
		// m_preview.OnRender();
	}

	void Game::Reset()
	{
		m_playfield.Reset();
		m_currentTetromino = m_playfield.GetNext();
		m_position = GetStartingPositionState(m_currentTetromino);
		m_gravTimer.Reset();
		m_inputTimer.Reset();
		
		m_gameOver = false;
	}

	PositionState Game::GetStartingPositionState(TetrominoType type)
	{
		switch (type)
		{
		case TetrominoType::I:
			return { -1, 3, 0 };
		case TetrominoType::O:
			return { 0, 4, 0 };
		case TetrominoType::T:
		case TetrominoType::S:
		case TetrominoType::Z:
		case TetrominoType::J:
		case TetrominoType::L:
			return { 0, 3, 0 };
		default: // ::None
			return { 0, 0, 0 };
		}
	}

	void Game::MoveTetrominoDown()
	{
		PositionState newState = m_position;
		newState.row++;
		if (ValidatePosition(newState))
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
		PositionState newState = m_position;
		newState.col--;
		if (ValidatePosition(newState))
		{
			m_position.col--;
		}
	}

	void Game::MoveTetriminoRight()
	{
		PositionState newState = m_position;
		newState.col++;
		if (ValidatePosition(newState))
		{
			m_position.col++;
		}
	}

	void Game::RotateTetromino()
	{
		PositionState newPos = m_position;
		newPos.rotation = (newPos.rotation + 1) % 4;
		if (!ValidatePosition(newPos))
		{
			 // first check if we can move down, if not return and do nothing, lock coming soon;
			newPos = m_position;
			newPos.row++;
			if (!ValidatePosition(newPos))
				return;
			
			// next check if we can move left, if not
			int adjustment = 1;
			if (m_position.col > 5)
			{
				adjustment = -1;
			}

			while (!ValidatePosition(m_position))
			{
				m_position.col += adjustment;
			}
			return;

			// then check if we can move right.

		}

		while (!ValidatePosition(m_position))
		{
			if (m_position.col < 5) // close to left wall
			{
				m_position.col++;
			}
			else // closer to right wall
			{
				m_position.col--;
			}
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

		m_currentTetromino = m_playfield.GetNext();
		m_position = GetStartingPositionState(m_currentTetromino);
		m_rotation = 0;

		if (!ValidatePosition(m_position))
		{
			m_gameOver = true;
		}
		
		uint32_t linesCleared = m_playfield.ClearLines();
		// TODO: update the score
	}

	
	bool Game::ValidatePosition(const PositionState& position)
	{
		const Tetromino& tetrInPlay = Tetrominoes::Tetrominoes[(int)m_currentTetromino][position.rotation];
		for (int i = 0; i < 4; i++)
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			if (!m_playfield.IsBlockEmpty((position.row + (int)offset.x), (position.col + (int)offset.y)))
			{
				return false;
			}
		}
		return true;
	}

	void Game::RenderCurrentTetromino(Renderer* pRenderer)
	{
		const Tetromino& tetrInPlay = Tetrominoes::Tetrominoes[(int)m_currentTetromino][m_rotation];
		for (int i = 0; i < 4; i++) // render the 4 blocks
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			Block anchor = m_playfield.GetBlock((m_position.row + (int)offset.x), (m_position.col + (int)offset.y));
			anchor.colorId = tetrInPlay.GetColorId();
			pRenderer->RenderBlock(anchor);
		}
	}

	void Game::RenderNextTetromino(Renderer* pRenderer)
	{
		
	}
}