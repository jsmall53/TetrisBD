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
		RenderRect(x, y, width, height, m_tetrColors[colorId]);
	}

	void Renderer::RenderRect(const int& x, const int& y, const int& width, const int& height, const Color& color)
	{
		ImageDrawRectangle(&m_image, x, y, width, height, color);
	}

	void Renderer::RenderBlock(const Block& block)
	{
		BlockColor colorId = block.colorId;
		if ((int)colorId > m_tetrColors.size())
			colorId = BlockColor::Default;
		RenderRect(block.x + 1, block.y + 1, block.size - 1, block.size - 1, m_tetrColors[(int)colorId]);
	}

	void Renderer::RenderText(const char* text, const int& x, const int& y)
	{
		ImageDrawText(&m_image, text, x, y, 15, RAYWHITE);
	}

	SectionRect Renderer::GetPlayfieldRect()
	{
		return { GetPlayFieldOffset(), 0, (int)(m_ctx.Width * m_ctx.PlayFieldRatio), m_ctx.Height };;
	}

	SectionRect Renderer::GetPreviewRect()
	{
		return { GetPreviewOffset(), 0, (int)(m_ctx.Width * m_ctx.PreviewRatio), m_ctx.Height };
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

	int Renderer::GetPreviewOffset()
	{
		int playfieldOffset = GetPlayFieldOffset();
		int playfieldWidth = (int)(m_ctx.Width * m_ctx.PlayFieldRatio);
		int previewOffset = playfieldOffset + playfieldWidth + m_ctx.BorderWidth;
		return previewOffset;
	}
}