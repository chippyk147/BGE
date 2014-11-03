#pragma once
#include "Game.h"

namespace BGE
{
	class Assignment : public Game
	{
	private:

	public:
		Assignment(void);
		~Assignment(void);
		bool Initialise();
		void Update();
		void Cleanup();
		void CreateWall();
	};
}

