#include "Assignment.h"

using namespace BGE;

Assignment::Assignment()
{
}


Assignment::~Assignment()
{
}

bool Assignment::Initialise()
{
	CreateWall();

	if (!Game::Initialise()) 
	{
		return false;
	}

	return true;
}

void Assignment::Cleanup()
{
	Game::Cleanup();
}

void Assignment::Update()
{
	Game::Update();
}

void Assignment::CreateWall()
{
	bool wallBuilt;
	int j = 5;
	int countBlocks = 0;

	for (int i = 1; i < 11; i++)
	{
		shared_ptr<PhysicsController> box1 = physicsFactory->CreateBox(5, 5, 5, glm::vec3(5 * i, j, 0), glm::quat());
		countBlocks++;

		if (i % 10 == 0)
		{
			j = j + 5;
			i = 0;
		}

		if (countBlocks == 100)
		{
			break;
		}
	}
}
