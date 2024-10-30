#pragma once
#include <cinttypes>
#include "tetromino.h"
#include "block.h"

namespace TetrisBD
{
	class Playfield
	{
	public:
		void Init();
		void OnUpdate();
		void OnRender();

	private:
		void InitBlocks();
		// 10 cells wide and 20 cells tall, with an additional 20 cell buffer zone 
		// above the top of the playfield, usually hidden or obstructed by the field frame.
		Block m_matrix[40][10];
	};
}