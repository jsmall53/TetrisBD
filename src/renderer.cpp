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

	void Renderer::RenderRect(int x, int y, int width, int height, Color color)
	{
		ImageDrawRectangle(&m_image, x, y, width, height, color);
	}

	void Renderer::RenderBlock(Block block)
	{

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