#pragma once

#include "Game.h";

namespace BGE
{
	class GravityController : public Game
	{
	public:
		GravityController();
		~GravityController();
		bool Initialise();
		void Update();
		void Cleanup();

		glm::vec3 gravity;
	};
}

