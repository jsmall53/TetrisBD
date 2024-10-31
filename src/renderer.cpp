#include "renderer.h"

namespace TetrisBD
{
	Renderer::Renderer(const RendererContext& ctx)
		:m_ctx(ctx)
	{
		m_image = GenImageColor(ctx.Width, ctx.Height, BLACK);
		m_texture = LoadTextureFromImage(m_image);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Update()
	{
		UpdateTexture(m_texture, m_image.data);
	}

	void Renderer::RenderNoise()
	{
		m_image = GenImagePerlinNoise(m_ctx.Width, m_ctx.Height, 0, 0, 0.5);
	}

	void Renderer::RenderRect(const int& x, const int& y, const int& width, const int& height, const int& colorId)
	{
		RenderRect(x, y, width, height, m_colors[colorId]);
	}

	void Renderer::RenderRect(const int& x, const int& y, const int& width, const int& height, const Color& color)
	{
		ImageDrawRectangle(&m_image, x, y, width, height, color);
	}

	void Renderer::RenderBlock(const Block& block)
	{
		BlockColor colorId = block.colorId;
		if ((int)colorId > m_colors.size())
			colorId = BlockColor::Default;
		RenderRect(block.x, block.y, block.size - 1, block.size - 1, m_colors[(int)colorId]);
	}

	SectionRect Renderer::GetPlayfieldRect()
	{
		SectionRect section;
		section.width = (int)(m_ctx.Width * m_ctx.PlayFieldRatio);
		section.height = m_ctx.Height;
		section.x = GetPlayFieldOffset();
		section.y = 0;
		return section;
	}

	int Renderer::GetScoreViewOffset()
	{
		return 0;
	}

	int Renderer::GetPlayFieldOffset()
	{
		int scoreViewOffset = GetScoreViewOffset();
		int scoreViewWidth = (int)(m_ctx.Width * m_ctx.ScoreViewRatio);
		int playfieldOffset = scoreViewOffset + scoreViewWidth + m_ctx.BorderWidth;
		return playfieldOffset;
	}
}