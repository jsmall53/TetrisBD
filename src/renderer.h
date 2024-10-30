#pragma once

#include <cinttypes>
#include <raylib.h>
#include <tetromino.h>

namespace TetrisBD
{
	struct RendererContext
	{
		int Width;
		int Height;
		float ScoreViewRatio;
		float PlayFieldRatio;
		float PreviewRatio;
		int BorderWidth;
	};

	struct SectionRect
	{
		int x;
		int y;
		int width;
		int height;
	};

	class Renderer
	{
	public:
		Renderer(const RendererContext& context);
		~Renderer();

		void Update();
		void RenderNoise();
		void RenderRect(int x, int y, int width, int height, Color color);
		void RenderBlock(Block block);

		SectionRect GetPlayfieldRect();
		int GetScoreViewOffset();
		int GetPlayFieldOffset();
		int GetPreviewOffset();


		const Texture2D& GetTexture() const { return m_texture; }
		int GetWidth() const { return m_ctx.Width; }
		int GetHeight() const { return m_ctx.Height; }


	private:
		RendererContext m_ctx;
		Image m_image;
		Texture2D m_texture;
	};
}