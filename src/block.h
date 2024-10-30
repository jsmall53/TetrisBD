#pragma once

#include <cinttypes>
#include "raylib.h"

namespace TetrisBD
{
	struct Block
	{
		uint32_t size = 30;
		int x;
		int y;
		uint32_t colorId = 0;
	};
}