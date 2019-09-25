#include "Prey.h"

Prey::Prey()
{}

Prey::~Prey()
{}

void Prey::PreyGenoParser()
{
	TCHAR currentDirectory[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, currentDirectory);

	strcat_s(currentDirectory, MAX_PATH, TEXT("\\Geno\\preygenotype.txt"));
	{
		struct stat buffer;
		if (stat(currentDirectory, &buffer) != 0)
		{
			printf_s("%s\nDirectory not found!", currentDirectory);
			assert(false);
		}
	}

	FILE* fp = nullptr;
	fopen_s(&fp, currentDirectory, "rt");
	char* line = nullptr;
	char temp[5] = { 0, };
	int i = 0;

	while (!feof(fp))
	{
		fgets(temp, sizeof(temp), fp);
		mPreyGeno[i] = temp[0];
		i++;
	}

	fclose(fp);
}

void Prey::PreyInit()
{
	for (int i = 0; i < sizeof(mPreyGeno); i++)
	{
		mPreyInt[i] = mPreyGeno[i] - '0';
	}

	for (int i = 0; i < mPreyInt[0] + 1; i++)
	{
		int length = (int)(1 + sqrt((double)mPreyInt[0]));
		dReal x = dReal((0.5 + (i / length)) / length * 8.0);
		dReal y = dReal((0.5 + (i % length)) / length * 8.0);
		dReal z = REAL(1.0) + REAL(0.1) * (dReal)drand48();

		PreyBodySides[i][0] = dReal(5 * (0.2 + 0.7 * drand48()) / sqrt((double)mPreyInt[0]));
		PreyBodySides[i][1] = dReal(5 * (0.2 + 0.7 * drand48()) / sqrt((double)mPreyInt[0]));
		PreyBodySides[i][2] = z;

		pPreyBody[i].create(pWorld);
		pPreyBody[i].setPosition(x, y, z);
		pPreyBody[i].setData((void*)(dsizeint)i);
		
		dMass tempMass;
		tempMass.setBox(1, PreyBodySides[i][0], PreyBodySides[i][1], PreyBodySides[i][2]);
		tempMass.adjust(REAL(0.1) * PreyBodySides[i][0] * PreyBodySides[i][1]);
		pPreyBody[i].setMass(&tempMass);

		pPreyGeom = dCreateBox(pSpace, (dReal)mPreyInt[1], (dReal)mPreyInt[2], (dReal)mPreyInt[3]);
		dGeomSetBody(pPreyGeom, pPreyBody[i].id());
	}
}

void Prey::PreyFitness()
{
}

void Prey::PreyGenoRenew()
{
	// Fitness 값에 의하여 preygenotype.txt 파일에 새롭게 입력
	// Prey 초기위치 벡터 저장(startPosition)
	// Simulation 끝난 후 위치 저장(EndPosition)
	// EndPosition - StartPosition, 이동거리 순으로 순서 정렬
	// Genetic Algorithm 으로 재배열
	// Mutate 추가
}

void Prey::ODEInitialize()
{
	for (int i = 0; i < sizeof(mPreyGeno); i++)
	{
		mPreyInt[i] = mPreyGeno[i] - '0';
	}

	for (int i = 0; i < mPreyInt[0] + 1; i++)
	{
		int length = (int)(1 + sqrt((double)mPreyInt[0]));
		dReal x = dReal((0.5 + (i / length)) / length * 8.0);
		dReal y = dReal((0.5 + (i % length)) / length * 8.0);
		dReal z = REAL(1.0) + REAL(0.1) * (dReal)drand48();

		PreyBodySides[i][0] = dReal(5 * (0.2 + 0.7 * drand48()) / sqrt((double)mPreyInt[0]));
		PreyBodySides[i][1] = dReal(5 * (0.2 + 0.7 * drand48()) / sqrt((double)mPreyInt[0]));
		PreyBodySides[i][2] = z;

		pPreyBody[i].create(pWorld);
		pPreyBody[i].setPosition(x, y, z);
		pPreyBody[i].setData((void*)(dsizeint)i);

		dMass tempMass;
		tempMass.setBox(1, PreyBodySides[i][0], PreyBodySides[i][1], PreyBodySides[i][2]);
		tempMass.adjust(REAL(0.1) * PreyBodySides[i][0] * PreyBodySides[i][1]);
		pPreyBody[i].setMass(&tempMass);

		pPreyGeom = dCreateBox(pSpace, (dReal)mPreyInt[1], (dReal)mPreyInt[2], (dReal)mPreyInt[3]);
		dGeomSetBody(pPreyGeom, pPreyBody[i].id());
	}
}

void Prey::ODEUpdate(int pause)
{
	double angle = (double)pause;
	for (int i = 0; i < mPreyInt[0]; i++)
	{
		double p = 1 + i / (double)mPreyInt[0];
		double q = 2 - i / (double)mPreyInt[0];
		pPreyBody[i].addForce(0.01 * cos(p * angle / 500), 0.01 * sin(q * angle / 500), 0);
	}

#if 1 /* [ */
	{
		for (int i = 0; i < mPreyInt[0]; i++)
		{
			const dReal* rot = dBodyGetAngularVel(pPreyBody[i].id());
			const dReal* quat_ptr;
			dReal quat[4], quat_len;

			quat_ptr = dBodyGetQuaternion(pPreyBody[i].id());
			quat[0] = quat_ptr[0];
			quat[1] = 0;
			quat[2] = 0;
			quat[3] = quat_ptr[3];

			quat_len = sqrt(quat[0] * quat[0] + quat[3] * quat[3]);
			quat[0] /= quat_len;
			quat[3] /= quat_len;
			dBodySetQuaternion(pPreyBody[i].id(), quat);
			dBodySetAngularVel(pPreyBody[i].id(), 0, 0, rot[2]);
		}
	}
#endif  /* ] */
}
