#pragma once
#include <cinttypes>
#include <raylib.h>

namespace TetrisBD
{
	enum class TetrominoType
	{
		None = 0,
		I,
		O,
		T,
		S,
		Z,
		J,
		L
	};

	struct Block
	{
		uint32_t size = 30;
		int x;
		int y;
		int colorId = 0;
	};

	// A tetromino object contains 4 "Blocks"
	// Use this class for the Tetromino currently in play and for the Tetromino on deck
	// once a tetromino is locked, move the Blocks to the playfield?
	class Tetromino
	{
	public:
		void OnUpdate();
		void OnRender();
	private:
		
		uint32_t m_blocks[4];
	};
}