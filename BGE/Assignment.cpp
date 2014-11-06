#include "Assignment.h"
#include "Utils.h"

using namespace BGE;

Assignment::Assignment()
{
}


Assignment::~Assignment()
{
}


shared_ptr<PhysicsController> cap1;

bool Assignment::Initialise()
{
	physicsFactory->CreateGroundPhysics();

	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	setGravity(glm::vec3(0, -9.81, 0));

	CreateWall();

	CreateAnimat();

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
	int j = 10;
	int countBlocks = 0;

	for (int i = 1; i < 11; i++)
	{
		shared_ptr<PhysicsController> box1 = physicsFactory->CreateSphere(2.49f, glm::vec3(5 * i, j, 0), glm::quat());
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

void Assignment::CreateAnimat()
{ 
	cap1 = physicsFactory->CreateCapsule(2.0f,10.0f, glm::vec3(30, 50, 100), glm::quat());


	//shared_ptr<PhysicsController> cap2 = physicsFactory->CreateCapsule(1.0f, 10.0f, glm::vec3(10, 50, 30), glm::quat());

	//btHingeConstraint * hinge = new btHingeConstraint(*cap1->rigidBody, *cap2->rigidBody, btVector3(0, 0, 0), btVector3(0, 0, -10.0f), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
	//dynamicsWorld->addConstraint(hinge);

	
}
