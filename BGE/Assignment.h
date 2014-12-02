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

		shared_ptr<PhysicsController>fishHead;
		float elapsed;
		bool floatUp;

		bool tailBalance;

		bool Initialise();
		void Update();
		void Cleanup();
		void CreateWall();
		void CreateAnimat();
	};
}

