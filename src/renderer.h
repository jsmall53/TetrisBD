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
		void RenderRect(const int& x, const int& y, const int& width, const int& height, const int& colorId);
		void RenderRect(const int& x, const int& y, const int& width, const int& height, const Color& color);
		void RenderBlock(const Block& block);
		void RenderText(const char* text, const int& x, const int& y);

		SectionRect GetPlayfieldRect();
		SectionRect GetPreviewRect();
		SectionRect GetScoreRect();
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
		
		static const int m_numColors = 9;
		Color m_tetrColors[m_numColors] =  // need 7 colors for the different tetrominoes + 1 for default block color
		{ 
			{ 0, 0, 0, 255 },
			{ 7, 203, 247, 255 }, // LIGHT BLUE = 1
			{ 245, 237, 7, 255 }, // YELLOW = 2
			{ 210, 7, 237, 255 }, // PURPLE = 3
			{ 50, 199, 52, 255 }, // GREEN = 4
			{ 255, 0, 0, 255 }, // RED = 5
			//{ 66, 26, 200, 255 }, // BLUE = 6
			{ 52, 85, 235, 255 }, // BLUE = 6
			{ 245, 137, 5, 255 }, // ORANGE = 7
			{ 15, 15, 75, 255 }, // DEFAULT PLAYFIELD COLOR = 8
		}; 
	};
}