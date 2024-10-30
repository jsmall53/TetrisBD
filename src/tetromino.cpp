#include "tetromino.h"
#include "application.h"

namespace TetrisBD
{
	Tetromino::Tetromino(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, TetrominoType type, uint32_t colorId)
		:m_type(type), m_colorId(colorId)
	{
		m_blocks[0] = v1;
		m_blocks[1] = v2;
		m_blocks[2] = v3;
		m_blocks[3] = v4;

	}

	void Tetromino::OnUpdate()
	{
		// TODO:
	}

	void Tetromino::OnRender(int x, int y)
	{
		Renderer* pRenderer = Application::GetRenderer();

		// TODO: 
	}

	Vector2 Tetromino::GetBlockOffset(int idx) const
	{
		if (idx < 0 || idx > 4)
			return { 0, 0 };
		return m_blocks[idx];
	}
}