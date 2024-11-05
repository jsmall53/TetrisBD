#pragma once
#include <cinttypes>
#include <vector>
#include <raylib.h>
#include "block.h"

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
		L,
		Max, // this needs to remain the last element
	};

	// A tetromino object contains 4 "Blocks"
	// Use this class for the Tetromino currently in play and for the Tetromino on deck
	// once a tetromino is locked, move the Blocks to the playfield?
	class Tetromino
	{
	public:
		Tetromino(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, TetrominoType type, BlockColor colorId);

		void OnUpdate();
		void OnRender(int x, int y);

		Vector2 GetBlockOffset(int idx) const;
		const TetrominoType& GetType() const { return m_type; }
		BlockColor GetColorId() const { return m_colorId; }

	private:
		TetrominoType m_type;
		BlockColor m_colorId;
		Vector2 m_blocks[4];
	};

	namespace Tetrominoes
	{
		inline Tetromino Tetrominoes[] =
		{
			// I
			Tetromino({ 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, TetrominoType::I, BlockColor::LightBlue),
			Tetromino({ 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, TetrominoType::I, BlockColor::LightBlue),
			Tetromino({ 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, TetrominoType::I, BlockColor::LightBlue),
			Tetromino({ 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, TetrominoType::I, BlockColor::LightBlue),

			// O
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, TetrominoType::O, BlockColor::Yellow),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, TetrominoType::O, BlockColor::Yellow),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, TetrominoType::O, BlockColor::Yellow),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, TetrominoType::O, BlockColor::Yellow),
		
			// T
			Tetromino({ 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, TetrominoType::T, BlockColor::Purple),
			Tetromino({ 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 1 }, TetrominoType::T, BlockColor::Purple),
			Tetromino({ 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 1 }, TetrominoType::T, BlockColor::Purple),
			Tetromino({ 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, TetrominoType::T, BlockColor::Purple),
			
			// S
			Tetromino({ 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, TetrominoType::S, BlockColor::Green),
			Tetromino({ 0, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, TetrominoType::S, BlockColor::Green),
			Tetromino({ 1, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 }, TetrominoType::S, BlockColor::Green),
			Tetromino({ 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, TetrominoType::S, BlockColor::Green),
		
			// Z
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 }, TetrominoType::Z, BlockColor::Red),
			Tetromino({ 0, 2 }, { 1, 1 }, { 1, 2 }, { 2, 1 }, TetrominoType::Z, BlockColor::Red),
			Tetromino({ 1, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 }, TetrominoType::Z, BlockColor::Red),
			Tetromino({ 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 0 }, TetrominoType::Z, BlockColor::Red),
		
			// J
			Tetromino({ 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, TetrominoType::J, BlockColor::Blue),
			Tetromino({ 0, 1 }, { 0, 2 }, { 1, 1 }, { 2, 1 }, TetrominoType::J, BlockColor::Blue),
			Tetromino({ 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, TetrominoType::J, BlockColor::Blue),
			Tetromino({ 0, 1 }, { 1, 1 }, { 2, 0 }, { 2, 1 }, TetrominoType::J, BlockColor::Blue),
		
			// L
			Tetromino({ 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, TetrominoType::L, BlockColor::Orange),
			Tetromino({ 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 2 }, TetrominoType::L, BlockColor::Orange),
			Tetromino({ 1, 0 }, { 1, 1 }, { 1, 2 }, { 2, 0 }, TetrominoType::L, BlockColor::Orange),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, TetrominoType::L, BlockColor::Orange),
		};

		inline Tetromino GetTetromino(const TetrominoType& type, const int& rotation)
		{
			return Tetrominoes[(((int)type - 1) * 4) + rotation];
		}

	}
}