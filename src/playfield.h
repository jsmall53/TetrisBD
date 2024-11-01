#pragma once

#include <random>
#include <cinttypes>
#include "block.h"
#include "renderer.h"

namespace TetrisBD
{
	class Playfield
	{
	public:
		Playfield();
		void OnUpdate();
		void OnRender();
		void Reset();

		TetrominoType GetNext();
		void SetBlock(const int& row, const int& col, const BlockColor& colorId);
		Block& GetBlock(const int& row, const int& col);
		bool IsBlockEmpty(const int& row, const int& col) const;
		uint32_t ClearLines();

	private:
		void InitBlocks();
		void ClearLine(int row);
		void RenderPlayfield(Renderer* pRenderer);
		void RenderNext(Renderer* pRenderer);
		TetrominoType RandomTetromino();

		// 10 cells wide and 20 cells tall, with an additional 20 cell buffer zone 
		// above the top of the playfield, usually hidden or obstructed by the field frame.
		Block m_matrix[40][10];
		int m_rowMax = 19;
		int m_colMax = 9;
		TetrominoType m_nextTetromino = TetrominoType::None;
		std::mt19937 m_randomGen;

		Color m_pfColor = { 15, 15, 75, 255 };
	};
}