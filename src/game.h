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
		static inline uint64_t s_linesPerLevel = 10;
	private:
		void RenderCurrentTetromino(Renderer* pRenderer);
		void RenderScore(Renderer* pRenderer);
		PositionState GetStartingPositionState(TetrominoType type);
		void MoveTetrominoDown();
		void MoveTetrominoLeft();
		void MoveTetriminoRight();
		void RotateTetromino();
		bool ValidatePosition(const PositionState& position);
		void LockTetromino();
		void UpdateScore(uint32_t linesCleared);
		void DropAndLock();
		
		Playfield m_playfield;
		PositionState m_position;
		TetrominoType m_currentTetromino = TetrominoType::None;
		Timer m_gravTimer;
		Timer m_inputTimer;
		bool m_gameOver = false;
		uint64_t m_score = 0;
		uint64_t m_linesCleared = 0;
		uint64_t m_level = 0;
	};
}
