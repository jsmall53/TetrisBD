//#include "block.h"
//#include "application.h"
//
//namespace TetrisBD
//{
//	Block::Block()
//		:m_x(-999), m_y(-999), m_size(-1), m_color(BLACK)
//	{ 
//	}
//
//	Block::Block(int x, int y, uint32_t cellSize, Color color)
//		:m_x(x), m_y(y), m_size(cellSize), m_color(color)
//	{
//	}
//
//	void Block::OnUpdate()
//	{
//
//	}
//
//	void Block::OnRender()
//	{
//		Renderer* pRenderer = Application::GetRenderer();
//		pRenderer->RenderBlock(*this);
//	}
//}