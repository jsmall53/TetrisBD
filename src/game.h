#pragma once

#include "playfield.h"

namespace TetrisBD
{
	class Game
	{
	public:
		Game();
		//~Game();

		void OnUpdate();
		void OnRender();

	private:
		Playfield m_playfield;
		
	};
}
