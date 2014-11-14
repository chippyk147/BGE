#include "Gravity.h"
#include "GravityController.h"

using namespace BGE;

Gravity::Gravity()
{
}


Gravity::~Gravity()
{
}

bool Gravity::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	
	shared_ptr<PhysicsController> sphere = physicsFactory->CreateSphere(5.0f,glm::vec3(10,10,10),glm::quat());
	
	sphere->Attach(make_shared<GravityController>());

	Attach(sphere);

	return Game::Initialise();
}

void Gravity::Update()
{
	Game::Update();
}

void Gravity::Cleanup()
{
	Game::Cleanup();
}