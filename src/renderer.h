#pragma once

#include <vector>
#include <cinttypes>
#include <raylib.h>
#include <tetromino.h>
#include "block.h"

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
		void RenderRect(const int& x, const int& y, const int& width, const int& height, const Color& color);
		void RenderBlock(const Block& block);

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
		
		std::vector<Color> m_colors // need 7 colors for the different tetrominoes + 1 for default block color
		{ 
			{ 15, 15, 75, 255 }
		}; 
	};
}