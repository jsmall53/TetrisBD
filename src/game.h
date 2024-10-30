#pragma once

#include "playfield.h"
#include "tetromino.h"

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

		Playfield m_playfield;
		PositionState m_position;
		TetrominoType m_currentTetromino = TetrominoType::None;
		TetrominoType m_nextTetromino = TetrominoType::None;
		int m_rotation = 0;

	};
}
