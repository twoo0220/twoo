#pragma once
#include "Prey.h"

constexpr unsigned int MAX_BUFFER = 50;

class MainClass : protected MainCore
{
public:
	static MainClass* Get()
	{
		static MainClass Instance;
		return &Instance;
	}
	
private:
	int simulateTime = 0;

public:
	virtual void ODEInitialize() override;
	virtual void ODEUpdate(int) override;

public:
	MainClass();
	~MainClass();

	Prey* cPrey;
	void Start(int argc, char** argv);
	void EffectorsServo(int time);
	static void nearCallback(void* data, dGeomID o1, dGeomID o2);
};

static MainClass* pMainClass = nullptr;