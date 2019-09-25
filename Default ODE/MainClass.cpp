#include "MainClass.h"
#include <cstdlib>
#include <ctime>

MainClass::MainClass()
{
	//ZeroMemory(&pBox, sizeof pBox);
	cPrey = new Prey();
}

MainClass::~MainClass()
{
	delete cPrey;
}

void MainClass::Start(int argc, char** argv)
{
	dsSimulationLoop(argc, argv, 800, 450, &dsFunction);
}

void MainClass::ODEInitialize()
{
	static float xyz[3] = { 0.0, -10.0, 0.0 };	// View position (x, y, z)[m]
	static float hpr[3] = { 90.0, -45.0, 0.0 };	// View direction (head, pitch, roll)[degree]

	dAllocateODEDataForThread(dAllocateMaskAll);
	dsSetViewpoint(xyz, hpr);					// Set view point
}

void MainClass::ODEUpdate(int pause)
{
	if (simulateTime == 0)
	{
		cPrey->PreyGenoParser();
		cPrey->PreyInit();
	}

	if (!pause) {
		static double angle = 0;
		angle += 5;
		if (angle >= 360) angle = 0.0;
		

		//for (int i = 0; i < 14; i++)
		//{
		//	dJointSetHingeParam(pJoint[i], dParamVel, 0.0);
		//	dJointSetHingeParam(pJoint[i], dParamFMax, 1000.0);
		//}

		//EffectorsServo(simulateTime);

		dSpaceCollide(pSpace, 0, &nearCallback);
		dWorldStep(pWorld, 0.01);

		/* remove all contact joints */
		dJointGroupEmpty(pContactGroup);
	}

	dsSetColor(1, 1, 0);
	dsSetTexture(DS_WOOD);

	for (int i = 0; i < cPrey->mPreyInt[0]; i++)
	{
		dsDrawBox(cPrey->pPreyBody[i].getPosition(), cPrey->pPreyBody->getRotation(), cPrey->PreyBodySides[i]);
	}

	simulateTime++;

	if (simulateTime > 1000)
	{
		simulateTime = 0;
	}
}

const double MAX_FORCE = 100000.0;
void MainClass::EffectorsServo(int time)
{
	//double SIGNAL[14];
	//double gain = 4.0;
	//double jStop = 0.3;

	//int jIdx = 7;

	////	double Joint_phase[14];

	//for (int jIdx = 2; jIdx < 15; jIdx++)
	//{
	//	if (jIdx == 4 || jIdx == 7 || jIdx == 12) {
	//		SIGNAL[jIdx] = 2 * sin(6.28 * 1.0 * time + 0.3);

	//		dReal DesiredAngle = SIGNAL[jIdx] * jStop;
	//		dReal TrueAngle = dJointGetHingeAngle(pJoint[jIdx]);
	//		dReal Error = DesiredAngle - TrueAngle;
	//		dReal desiredMotorSpeed = gain * Error;

	//		dJointSetHingeParam(pJoint[jIdx], dParamFMax, MAX_FORCE);
	//		dJointSetHingeParam(pJoint[jIdx], dParamVel, desiredMotorSpeed);
	//	}
	//	else if (jIdx == 3 || jIdx == 8 || jIdx == 11) {
	//		SIGNAL[jIdx] = -2 * sin(6.28 * 1.0 * time + 0.3);

	//		dReal DesiredAngle = SIGNAL[jIdx] * jStop;
	//		dReal TrueAngle = dJointGetHingeAngle(pJoint[jIdx]);
	//		dReal Error = DesiredAngle - TrueAngle;
	//		dReal desiredMotorSpeed = gain * Error;

	//		dJointSetHingeParam(pJoint[jIdx], dParamFMax, MAX_FORCE);
	//		dJointSetHingeParam(pJoint[jIdx], dParamVel, desiredMotorSpeed);
	//	}
	//}
}

void MainClass::nearCallback(void* data, dGeomID o1, dGeomID o2)
{
	const int N = 15;
	dContact contact[N];
	dBodyID b1, b2;

	b1 = dGeomGetBody(o1);
	b2 = dGeomGetBody(o2);
	if (b1 && b2 && dAreConnected(b1, b2)) return;

	int n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));

	for (int i = 0; i < n; i++) {
		contact[i].surface.mode = dContactSoftERP | dContactSoftCFM | dContactApprox1;
		contact[i].surface.mu = 0.2;
		//contact[i].surface.slip1 = 0.01;
		contact[i].surface.soft_erp = 0.2;
		contact[i].surface.soft_cfm = 0.001;

		dJointID c = dJointCreateContact(MainClass::Get()->pWorld, MainClass::Get()->pContactGroup, &contact[i]);
		dJointAttach(c, b1, b2);
	}
}