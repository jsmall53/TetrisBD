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
		if (IsKeyPressed(KEY_UP)) // ROTATION
			RotateTetromino();
		else if (IsKeyPressed(KEY_SPACE)) //HARD DROP
		{
			DropAndLock();
		}
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
		RenderScore(pRenderer);

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
		m_score = 0;
		m_linesCleared = 0;
		m_level = 0;
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
		int rotation = (m_position.rotation + 1) % 4;
		PositionState newPos = m_position;
		newPos.rotation = rotation;
		if (!ValidatePosition(newPos))
		{
			 // first check if we can move down, if not return and do nothing, lock coming soon;
			newPos = m_position;
			newPos.row++;
			if (!ValidatePosition(newPos))
				return;
			
			newPos.rotation = rotation;
			// next check if we can move left, if not
			int adjustment;
			if (m_position.col > 5)
			{
				adjustment = -1;
			}
			else
			{
				adjustment = 1;
			}

			while (!ValidatePosition(newPos))
			{
				newPos.col += adjustment;
			}
		}

		m_position = newPos;
	}

	void Game::LockTetromino()
	{
		const Tetromino& tetrInPlay = Tetrominoes::GetTetromino(m_currentTetromino, m_position.rotation);
		const BlockColor& colorId = tetrInPlay.GetColorId();
		for (int i = 0; i < 4; i++)
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			m_playfield.SetBlock((m_position.row + (int)offset.x), (m_position.col + (int)offset.y), colorId);
		}

		m_currentTetromino = m_playfield.GetNext();
		m_position = GetStartingPositionState(m_currentTetromino);

		if (!ValidatePosition(m_position))
		{
			m_gameOver = true;
		}
		
		uint32_t linesCleared = m_playfield.ClearLines();
		UpdateScore(linesCleared);
		m_linesCleared += linesCleared;
		m_level = m_linesCleared / s_linesPerLevel;
	}

	void Game::UpdateScore(uint32_t linesCleared)
	{
		if (linesCleared == 0)
			return;

		uint64_t base = 0;
		switch (linesCleared)
		{
		case 1:
			base = 40;
			break;
		case 2:
			base = 100;
			break;
		case 3:
			base = 300;
			break;
		case 4: // TETRIS FOR JONAS
			base = 1200;
			break;
		}

		int levelMultipler = 1; // TODO: implement levels
		m_score += base * levelMultipler;
	}

	void Game::DropAndLock()
	{
		int startingRow = m_position.row;
		auto newState = m_position;
		while (ValidatePosition(newState))
		{
			newState.row++;
		}
		newState.row--;
		m_position = newState;
		m_score += m_position.row - startingRow + 1;
		LockTetromino();
		
	}
	

	bool Game::ValidatePosition(const PositionState& position)
	{
		const Tetromino& tetrInPlay = Tetrominoes::GetTetromino(m_currentTetromino, position.rotation);
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
		const Tetromino& tetrInPlay = Tetrominoes::GetTetromino(m_currentTetromino, m_position.rotation);
		for (int i = 0; i < 4; i++) // render the 4 blocks
		{
			Vector2 offset = tetrInPlay.GetBlockOffset(i);
			Block anchor = m_playfield.GetBlock((m_position.row + (int)offset.x), (m_position.col + (int)offset.y));
			anchor.colorId = tetrInPlay.GetColorId();
			pRenderer->RenderBlock(anchor);
		}
	}

	void Game::RenderScore(Renderer* pRenderer)
	{
		SectionRect scoreRect = pRenderer->GetScoreRect();
		scoreRect.height /= 3;
		pRenderer->RenderRect(scoreRect.x, scoreRect.y, scoreRect.width, scoreRect.height, 8);
		int xPos = scoreRect.x + (scoreRect.width / 3);
		int yPos = scoreRect.y + (scoreRect.height * 0.25f);
		
		std::string levelText = std::format("Level: {}", m_level);
		pRenderer->RenderText(levelText.c_str(), xPos + 6, yPos);
		
		std::string scoreText = std::format("Score: {}", m_score);
		pRenderer->RenderText(scoreText.c_str(), xPos + 6, yPos + 25);

	}
}