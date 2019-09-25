#pragma once
#include "MainCore.h"

#define drand48() ((double) (((double) rand()) / ((double) RAND_MAX)))

class Prey : protected MainCore
{
public:
	//static Prey* Get()
	//{
	//	static Prey Instance;
	//	return &Instance;
	//}

public:
	Prey();
	~Prey();

public:
	void PreyGenoParser();
	void PreyInit();
	void PreyFitness();
	void PreyGenoRenew();

public:
	dBody pPreyBody[COUNT_MAX];
	dGeomID pPreyGeom;
	dMass PreyMass;
	dReal PreyBodySides[COUNT_MAX][3] = { 0, };

	char mPreyGeno[20] = { 0, };
	int mPreyInt[20] = { 0, };

public:
	//void ODEInitialize();
	//void ODEUpdate(int);
	virtual void ODEInitialize() override;
	virtual void ODEUpdate(int) override;
};

//static Prey* pPreyClass = nullptr;