#pragma once

#include "playfield.h"
#include "tetromino.h"
#include "timer.h"

namespace TetrisBD
{
	struct PositionState
	{
		int row;
		int col;
	};

	class Game
	{
	public:
		Game();

		void OnUpdate();
		void OnRender();

	private:
		PositionState GetStartingPositionState(TetrominoType type);
		void MoveTetrominoDown();
		void MoveTetrominoLeft();
		void MoveTetriminoRight();
		void RotateTetromino();
		bool CanBlockMove(int row, int col);
		void LockTetromino();
		TetrominoType RandomTetromino();

		Playfield m_playfield;
		PositionState m_position;
		TetrominoType m_currentTetromino = TetrominoType::None;
		TetrominoType m_nextTetromino = TetrominoType::None;
		int m_rotation = 0;
		Timer m_gravTimer;
	};
}
