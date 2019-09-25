#pragma once
#include "MainCore.h"

class Predator : protected MainCore
{
	Predator();
	~Predator();

public:
	void PredatorGenoParser();
	void PredatorInit();
	void PredatorGenoRenew();

private:
	dBody pPredatorBody[COUNT_MAX];
	dGeomID pPredatorGeom[COUNT_MAX];

	char mPredatorGeno[20];
	int mPredatorInt[20] = { 0, };
};

