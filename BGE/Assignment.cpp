#include "Assignment.h"
#include "Utils.h"
#include "Content.h"
#include "VectorDrawer.h"

using namespace BGE;

Assignment::Assignment()
{
}


Assignment::~Assignment()
{
}

shared_ptr<PhysicsController>bodyPart, lastBodyPart, toptailBodyPart, bottomtailBodyPart, flippers1, flippers2, dorsalFin;

bool Assignment::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();

	shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);

	setGravity(glm::vec3(0, -19.81, 0));
	elapsed = 0;
	floatUp = false;
	tailBalance = false;

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
	elapsed += Time::deltaTime;

	if (floatUp == true)
	{
		dorsalFin->rigidBody->applyForce(btVector3(0, 2000.0f, 0.0f), btVector3(0, 0, 0));

		if (dorsalFin->transform->position.y > 50.0f)
		{
			floatUp = false;
		}
	}
	if (dorsalFin->transform->position.y < 50.0f)
	{
		floatUp = true;
	}

	if (tailBalance == true)
	{
		toptailBodyPart->rigidBody->applyForce(btVector3(0, 500.0f, 0.0f), btVector3(0, 0, 0));
		bottomtailBodyPart->rigidBody->applyForce(btVector3(0, 500.0f, 0.0f), btVector3(0, 0, 0));

		if (toptailBodyPart->transform->position.y > 30.0f)
		{
			tailBalance = false;
		}
	}
	if (toptailBodyPart->transform->position.y < 30.0f)
	{
		tailBalance = true;
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		fishHead->rigidBody->applyTorque(btVector3(0.0f, 25000.0f, 0.0f));
	}
	else if (keyState[SDL_SCANCODE_LEFT])
	{
		fishHead->rigidBody->applyTorque(btVector3(0.0f, -25000.0f, 0.0f));
	}
	else if (keyState[SDL_SCANCODE_DOWN])
	{
		dorsalFin->rigidBody->applyForce(btVector3(0, -2000.0f, 0.0f), btVector3(0, 0, 0));
	}


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
	int loc = 0;

	glm::quat qFishHead1 = glm::angleAxis(90.0f, glm::vec3(1, 0, 0));
	glm::quat qFishHead2 = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));

	fishHead = physicsFactory->CreateBox(1, 10, 10, glm::vec3(0, 20, 25), qFishHead1 * qFishHead2, false, true);
	fishHead->transform->diffuse = glm::vec3(0.28f, 0.79f, 0.77f);

	lastBodyPart = fishHead;

	glm::quat qRotTailTop = glm::angleAxis(30.f, glm::vec3(0, 0, -1));
	glm::quat qRotTailBottom = glm::angleAxis(30.f, glm::vec3(0, 0, 1));
	glm::quat qFlip1 = glm::angleAxis(45.0f, glm::vec3(-1, 0, -1));
	glm::quat qFlip2 = glm::angleAxis(45.0f, glm::vec3(1, 0, -1));
	glm::quat qDorsalFin = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
	glm::quat qDorsalFin2 = glm::angleAxis(135.0f, glm::vec3(0, 0, 1));

	glm::vec3 none = glm::vec3(0, 0, 0);

	toptailBodyPart = physicsFactory->CreateBox(5, 10, 1, glm::vec3(60, 27, 25), qRotTailTop, false, true);
	bottomtailBodyPart = physicsFactory->CreateBox(5, 10, 1, glm::vec3(60, 13, 25), qRotTailBottom, false, true);

	toptailBodyPart->transform->diffuse = glm::vec3(0.94f, 0.14f, 0.22f);
	bottomtailBodyPart->transform->diffuse = glm::vec3(0.94f, 0.14f, 0.22f);

	flippers1 = physicsFactory->CreateBox(5, 5, 1, glm::vec3(20, 15, 30), qFlip1, false, true); 
	flippers2 = physicsFactory->CreateBox(5, 5, 1, glm::vec3(20, 15, 22), qFlip2, false, true);

	flippers1->transform->diffuse = glm::vec3(0.94f, 0.14f, 0.22f);
	flippers2->transform->diffuse = glm::vec3(0.94f, 0.14f, 0.22f);

	dorsalFin = physicsFactory->CreateBox(8, 10, 1, glm::vec3(20, 30, 25), qDorsalFin2, false, true);
	dorsalFin->transform->diffuse = glm::vec3(0.94f, 0.14f, 0.22f);

	glm::quat q = glm::angleAxis(90.f, glm::vec3(0, 0, 1));

	for (int i = 0; i < 4; i++)
	{
		loc += (10 + 1);
		bodyPart = physicsFactory->CreateCylinder(1, 5.0f, glm::vec3(loc,20,25),q,false,true);
		bodyPart->transform->diffuse = glm::vec3(glm::vec3(0.28f, 0.79f, 0.77f));

		btHingeConstraint * hinge = new btHingeConstraint(*lastBodyPart->rigidBody, *bodyPart->rigidBody, btVector3(0, -8, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0, 1, 0), true);
		hinge->setLimit(btScalar(0.0f), btScalar(0.0f));

		if (i == 1)
		{
			btConeTwistConstraint * hingeB = new btConeTwistConstraint(*lastBodyPart->rigidBody, *flippers1->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(105.0f, glm::vec3(0, 1, 0))), GLToBtVector(glm::vec3(0, 0, 0))), btTransform(GLToBtQuat(qFlip1), GLToBtVector(glm::vec3(0, 10, 0))));
			hingeB->setLimit(0.0f, 0.0f, 0.5f);
			dynamicsWorld->addConstraint(hingeB);
			hingeB = new btConeTwistConstraint(*lastBodyPart->rigidBody, *flippers2->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(75.0f, glm::vec3(0, 1, 0))), GLToBtVector(glm::vec3(0, 0, 0))), btTransform(GLToBtQuat(qFlip2), GLToBtVector(glm::vec3(0, 10, 0))));
			hingeB->setLimit(0.0f, 0.0f, 0.5f);
			dynamicsWorld->addConstraint(hingeB);
		}

		if (i == 2)
		{
			btFixedConstraint * hingeC = new btFixedConstraint(*lastBodyPart->rigidBody, *dorsalFin->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 1, 0))), GLToBtVector(glm::vec3(0, 5, 5))), btTransform(GLToBtQuat(qDorsalFin), GLToBtVector(glm::vec3(0, 10, 0))));
			dynamicsWorld->addConstraint(hingeC);
		}

		dynamicsWorld->addConstraint(hinge);

		lastBodyPart = bodyPart;
	}

	btFixedConstraint * hingeA = new btFixedConstraint(*lastBodyPart->rigidBody, *toptailBodyPart->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 1, 0))), GLToBtVector(glm::vec3(0, 8, 0))), btTransform(GLToBtQuat(qRotTailTop), GLToBtVector(glm::vec3(0, 15, 0))));
	dynamicsWorld->addConstraint(hingeA);

	hingeA = new btFixedConstraint(*lastBodyPart->rigidBody, *bottomtailBodyPart->rigidBody, btTransform(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 1, 0))), GLToBtVector(glm::vec3(0, 8, 0))), btTransform(GLToBtQuat(qRotTailBottom), GLToBtVector(glm::vec3(0, 15, 0))));
	dynamicsWorld->addConstraint(hingeA);
}
