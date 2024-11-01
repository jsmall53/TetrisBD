#pragma once

#include "renderer.h"
#include "playfield.h"
#include "tetromino.h"
#include "timer.h"

namespace TetrisBD
{
	struct PositionState
	{
		int row;
		int col;
		int rotation;
	};

	class Game
	{
	public:
		Game();

		void OnUpdate();
		void OnRender();
		void Reset();

	private:
		void RenderCurrentTetromino(Renderer* pRenderer);
		void RenderNextTetromino(Renderer* pRenderer);
		PositionState GetStartingPositionState(TetrominoType type);
		void MoveTetrominoDown();
		void MoveTetrominoLeft();
		void MoveTetriminoRight();
		void RotateTetromino();
		bool ValidatePosition(const PositionState& position);
		void LockTetromino();
		
		Playfield m_playfield;
		PositionState m_position;
		TetrominoType m_currentTetromino = TetrominoType::None;
		Timer m_gravTimer;
		Timer m_inputTimer;
		bool m_gameOver = false;
	};
}
