#pragma once
#include "stdafx.h"

constexpr double GRAVITY = 9.81;
class MainCore
{
protected:
	dsFunctions dsFunction;
	dWorldID pWorld;
	dSpaceID pSpace;
	dJointGroupID pContactGroup;

public:
	MainCore();
	~MainCore();

	void Release();

	virtual void ODEInitialize() = 0;
	virtual void ODEUpdate(int) = 0;

private:
	static void Start();
	static void Step(int pause);
};

static MainCore* pMainCore = nullptr;
