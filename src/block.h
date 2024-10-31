#pragma once

#include <cinttypes>
#include "raylib.h"

namespace TetrisBD
{
	enum class BlockColor
	{
		Default = 0,
		LightBlue,
		Yellow,
		Purple,
		Green,
		Red,
		Blue,
		Orange,
	};

	struct Block
	{
		uint32_t size = 30;
		int x;
		int y;
		BlockColor colorId = BlockColor::Default;
	};
}