#include "MainCore.h"

MainCore::MainCore()
	:dsFunction({ 0, })
{
	pMainCore = this;

	dsFunction.version = DS_VERSION;
	dsFunction.start = Start;
	dsFunction.step = Step;
	dsFunction.path_to_textures = "Resources\\Textures";

	/* create world */
	dInitODE2(0);

	pWorld = dWorldCreate();
	pSpace = dHashSpaceCreate(0);
	pContactGroup = dJointGroupCreate(0);

	dWorldSetGravity(pWorld, 0, 0, -GRAVITY);
	dCreatePlane(pSpace, 0, 0, 1, 0);
}


MainCore::~MainCore()
{
}

void MainCore::Release()
{
	dJointGroupDestroy(pContactGroup);
	dSpaceDestroy(pSpace);
	dWorldDestroy(pWorld);

	dCloseODE();
}

void MainCore::Start()
{
	pMainCore->ODEInitialize();
}

void MainCore::Step(int pause)
{
	if (KeyCode->isKeyDown(VK_ESCAPE))
	{
		pMainCore->Release();
		exit(-1);
		return;
	}

	pMainCore->ODEUpdate(pause);
}