#include "Lab3.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"

using namespace BGE;

Lab3::Lab3(void)
{
	elapsed = 10000;
}


bool Lab3::Initialise()
{
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);	

	ship1 = make_shared<GameComponent>(true);
	ship1->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship1->Attach(make_shared<VectorDrawer>(glm::vec3(5,5,5)));
	ship1->transform->position = glm::vec3(-10, 2, -10);
	Attach(ship1);

	ship2 = make_shared<GameComponent>(true);
	ship2->Attach(Content::LoadModel("python", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship2->Attach(make_shared<VectorDrawer>(glm::vec3(5,5,5)));
	ship2->transform->position = glm::vec3(10, 2, -10);
	Attach(ship2);
	Game::Initialise();

	camera->transform->position = glm::vec3(0, 4, 20);
	return true;
}

void Lab3::Update(float timeDelta)
{
	static float timeToFire = 1.0f / 2.0f;

	// Movement of ship2
	if (keyState[SDL_SCANCODE_UP])
	{
		ship2->transform->position += ship2->transform->look * speed * timeDelta;
	}
	if (keyState[SDL_SCANCODE_DOWN])
	{
		ship2->transform->position -= ship2->transform->look * speed * timeDelta;
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		ship2->transform->Yaw(-rotation_speed*timeDelta);
	}
	if (keyState[SDL_SCANCODE_LEFT])
	{
		ship2->transform->Yaw(rotation_speed*timeDelta);
	}

	if (keyState[SDL_SCANCODE_U])
	{
		ship1->transform->position += ship1->transform->look * speed * timeDelta;
	}
	if (keyState[SDL_SCANCODE_J])
	{
		ship1->transform->position -= ship1->transform->look * speed * timeDelta;
	}
	if (keyState[SDL_SCANCODE_K])
	{
		ship1->transform->Yaw(-rotation_speed*timeDelta);
	}
	if (keyState[SDL_SCANCODE_H])
	{
		ship1->transform->Yaw(rotation_speed*timeDelta);
	}

	glm::vec3 c = ship2->transform->position - ship1->transform->position;

	float lenC = glm::length(c);

	PrintFloat("Length:",lenC);

	float invC = glm::dot(ship1->transform->look, c);

	if (invC > 0)
	{
		PrintText("Infront");
	}
	if (invC < 0)
	{
		PrintText("Behind");
	}

	float theta = glm::acos(invC / lenC);

	if (theta < glm::radians(45.0f))
	{
		PrintText("Inside FOV");

		if (elapsed > timeToFire)
		{
			shared_ptr<LazerBeam> lazer = make_shared<LazerBeam>();
			Attach(lazer);
			lazer->transform->position = ship1->transform->position;
			lazer->transform->position += lazer->transform->look * speed * timeDelta;
			elapsed = 0;
		}
	}
	else
	{
		PrintText("Oustide FOV");
	}

	PrintFloat("Elapsed:",elapsed);
	PrintFloat("Timedelta:", timeDelta);

	elapsed += timeDelta;

	Game::Update(timeDelta);
}
