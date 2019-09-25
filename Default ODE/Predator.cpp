#include "Predator.h"

Predator::Predator()
{
}

Predator::~Predator()
{
}

void Predator::PredatorGenoParser()
{
	FILE* fp;
	char* temp;
	errno_t err = fopen_s(&fp, "Geno/predatorgenotype.txt", "r");

	assert(err);

	mPredatorGeno[0] = { 0, };

	while (1)
	{
		temp = fgets(mPredatorGeno, sizeof(mPredatorGeno), fp);

		if (temp == NULL)
		{
			break;
		}
	}

	fclose(fp);
}

void Predator::PredatorInit()
{
}

void Predator::PredatorGenoRenew()
{
}
