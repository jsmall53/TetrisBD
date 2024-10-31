#include "playfield.h"
#include "application.h"

namespace TetrisBD
{
	void Playfield::Init()
	{
		InitBlocks();
	}

	void Playfield::OnUpdate()
	{

	}

	void Playfield::OnRender()
	{
		Renderer* pRenderer = Application::GetRenderer();

		// TODO; fix default rendering color and color instantiation here...
		auto rect = pRenderer->GetPlayfieldRect();
		pRenderer->RenderRect(rect.x, rect.y, rect.width, rect.height, 0);
		for (int row = 0; row < 20; row++)
		{
			for (int col = 0; col < 10; col++)
			{
				pRenderer->RenderBlock(m_matrix[row][col]);
			}
		}
	}

	void Playfield::Reset()
	{
		InitBlocks();
	}

	void Playfield::SetBlock(const int& row, const int& col, const BlockColor& colorId)
	{
		m_matrix[row][col].colorId = colorId;
	}

	Block& Playfield::GetBlock(const int& row, const int& col)
	{
		return m_matrix[row][col];
	}

	bool Playfield::IsBlockEmpty(const int& row, const int& col) const
	{
		if (row > m_rowMax || col < 0 || col > m_colMax)
			return false;
		return m_matrix[row][col].colorId == BlockColor::Default;
	}

	void Playfield::InitBlocks()
	{
		Renderer* pRenderer = Application::GetRenderer();
		if (pRenderer)
		{
			auto rect = pRenderer->GetPlayfieldRect();
			Color blockColor{ 15, 15, 75, 255 };

			int maxHeight = (rect.height) / 20;
			int maxWidth = (rect.width) / 10;
			int cellSize = maxHeight < maxWidth ? maxHeight : maxWidth;
			int xOffset = (rect.width - (cellSize * 10)) / 2;
			//int yOffset = (rect.height - rect.y) - ((rect.height - (cellSize * 20)) / 2);
			int yOffset = ((rect.height - (cellSize * 20)) / 2);
			for (int row = 0; row < 20; row++)
			{
				//int yPos = yOffset - ((row + 1) * cellSize);
				int yPos = yOffset + (row * cellSize);
				for (int col = 0; col < 10; col++)
				{
					int xPos = xOffset + (col * cellSize) + rect.x;
					m_matrix[row][col].size = cellSize;
					m_matrix[row][col].x = xPos;
					m_matrix[row][col].y = yPos;
					m_matrix[row][col].colorId = BlockColor::Default;
				}
			}
		}

	}
}