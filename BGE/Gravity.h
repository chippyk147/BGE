#pragma once
#include "Game.h";

namespace BGE
{
	class Gravity : public Game
	{
	public:
		Gravity();
		~Gravity();
		bool Initialise();
		void Update();
		void Cleanup();
	};
}

