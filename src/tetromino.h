#pragma once
#include <cinttypes>
#include <vector>
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

	// A tetromino object contains 4 "Blocks"
	// Use this class for the Tetromino currently in play and for the Tetromino on deck
	// once a tetromino is locked, move the Blocks to the playfield?
	class Tetromino
	{
	public:
		Tetromino(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, TetrominoType type, uint32_t colorId); // this feels terrible lmao

		void OnUpdate();
		void OnRender(int x, int y);

		Vector2 GetBlockOffset(int idx) const;
		const TetrominoType& GetType() const { return m_type; }
		uint32_t GetColorId() const { return m_colorId; }

	private:
		TetrominoType m_type;
		uint32_t m_colorId;
		Vector2 m_blocks[4];
	};

	namespace Tetrominoes
	{
		inline std::vector<Tetromino> ITetromino = 
		{
			Tetromino({ 1, 0 }, { 1, 1 }, { 1,2 }, { 1,3 }, TetrominoType::I, 1),
			Tetromino({ 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, TetrominoType::I, 1),
			Tetromino({ 1, 0 }, { 1, 1 }, { 1,2 }, { 1,3 }, TetrominoType::I, 1),
			Tetromino({ 1, 0 }, { 1, 1 }, { 1,2 }, { 1,3 }, TetrominoType::I, 1),
		};

		inline std::vector<Tetromino> OTetromino =
		{
			Tetromino({ 0, 0 }, { 0, 1 }, { 1,0 }, { 1,1 }, TetrominoType::O, 2),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1,0 }, { 1,1 }, TetrominoType::O, 2),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1,0 }, { 1,1 }, TetrominoType::O, 2),
			Tetromino({ 0, 0 }, { 0, 1 }, { 1,0 }, { 1,1 }, TetrominoType::O, 2),
		};

		inline std::vector<std::vector<Tetromino>> Tetrominoes =
		{
			std::vector<Tetromino>(), // empty for TetrominoType == 0
			ITetromino,
			OTetromino,
		};
	}
}