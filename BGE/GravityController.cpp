#include "GravityController.h"
#include "Utils.h"

using namespace BGE;

GravityController::GravityController()
{
	gravity = glm::vec3(0, -9.81, 0);
}


GravityController::~GravityController()
{
}

bool GravityController::Initialise()
{
	return Game::Initialise();
}

void GravityController::Update()
{
	transform->velocity += gravity * Time::deltaTime;
	transform->position = transform->velocity * Time::deltaTime;

	if (transform->position.y - transform->scale.x < 0)
	{
		transform->velocity -= transform->velocity;
	}

	Game::Update();
}

void GravityController::Cleanup()
{
	Game::Cleanup();
}
