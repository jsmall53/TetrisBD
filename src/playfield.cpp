#include "playfield.h"
#include "application.h"

namespace TetrisBD
{
	Playfield::Playfield()
	{
		std::random_device rd;
		m_randomGen = std::mt19937(rd());
	}

	void Playfield::OnUpdate()
	{

	}

	void Playfield::OnRender()
	{
		Renderer* pRenderer = Application::GetRenderer();

		RenderPlayfield(pRenderer);
		RenderNext(pRenderer);
	}

	void Playfield::RenderPlayfield(Renderer* pRenderer)
	{
		auto rect = pRenderer->GetPlayfieldRect();
		pRenderer->RenderRect(rect.x, rect.y, rect.width, rect.height, m_pfColor);

		const Block& reference = m_matrix[0][0];
		pRenderer->RenderRect(reference.x, reference.y, (reference.size * 10) + 1, (reference.size * 20) + 1, m_pfColor);

		for (int row = 0; row < 20; row++)
		{
			for (int col = 0; col < 10; col++)
			{
				pRenderer->RenderBlock(m_matrix[row][col]);
			}
		}
	}

	void Playfield::RenderNext(Renderer* pRenderer)
	{
		SectionRect previewRect = pRenderer->GetPreviewRect();
		previewRect.height /= 3;
		pRenderer->RenderRect(previewRect.x, previewRect.y, previewRect.width, previewRect.height, m_pfColor);
		const Tetromino& nextTetr = Tetrominoes::Tetrominoes[(int)m_nextTetromino][0];
		Block anchor;
		int xPos = previewRect.x + (previewRect.width / 3);
		int yPos = previewRect.y + (previewRect.height * 0.4f);
		anchor.colorId = nextTetr.GetColorId();
		anchor.size = GetBlock(0, 0).size;
		for (int i = 0; i < 4; i++)
		{
			Vector2 offset = nextTetr.GetBlockOffset(i);
			int row = offset.x;
			int col = offset.y;
			anchor.x = xPos + (col * anchor.size);
			anchor.y = yPos + (row * anchor.size);
			pRenderer->RenderBlock(anchor);
		}
		
		yPos = previewRect.y + (previewRect.height * 0.25f);
		pRenderer->RenderText("Next", xPos + 6, yPos);
	}

	void Playfield::Reset()
	{
		InitBlocks();
		m_nextTetromino = RandomTetromino();
	}

	TetrominoType Playfield::GetNext()
	{
		TetrominoType ret = m_nextTetromino;
		m_nextTetromino = RandomTetromino();
		return ret;
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

	uint32_t Playfield::ClearLines()
	{
		uint32_t linesCleared = 0;
		for (int row = 0; row <= m_rowMax; row++)
		{
			bool rowFull = true;
			for (int col = 0; col <= m_colMax; col++)
			{
				if (IsBlockEmpty(row, col))
				{
					rowFull = false;
					break;
				}
			}

			if (rowFull)
			{
				ClearLine(row);
				linesCleared++;
			}
		}

		return linesCleared;
	}

	void Playfield::ClearLine(int row)
	{
		for (int rowClear = row; rowClear > 0; rowClear--)
		{
			for (int col = 0; col <= m_colMax; col++)
			{
				m_matrix[rowClear][col].colorId = m_matrix[rowClear - 1][col].colorId;
			}
		}
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

	TetrominoType Playfield::RandomTetromino()
	{
		int min = (int)(TetrominoType::None)+1;
		int max = (int)(TetrominoType::Max)-1;
		std::uniform_int_distribution<int> dist(min, max);
		return (TetrominoType)dist(m_randomGen);
	}

}