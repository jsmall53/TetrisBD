#pragma once

#include <random>
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
		TetrominoType RandomTetromino();

		Playfield m_playfield;
		PositionState m_position;
		TetrominoType m_currentTetromino = TetrominoType::None;
		TetrominoType m_nextTetromino = TetrominoType::None;
		int m_rotation = 0;
		Timer m_gravTimer;
		Timer m_inputTimer;
		bool m_gameOver = false;

		std::mt19937 m_randomGen;
	};
}
