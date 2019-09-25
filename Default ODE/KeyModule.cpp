#include "KeyModule.h"
#include "stdafx.h"

KeyModule::KeyModule()
{
	ZeroMemory(bKeyDown, sizeof bKeyDown);
	ZeroMemory(PrevKey, sizeof PrevKey);
}

KeyModule::~KeyModule()
{
}

bool KeyModule::isKeyDown(int inner)
{
	if (GetAsyncKeyState(inner) & 0x8000) {
		if (!bKeyDown[inner]) {
			bKeyDown[inner] = 0x01;
			return true;
		}
	}
	else bKeyDown[inner] = 0;

	return false;
}

bool KeyModule::StayKeyDown(int inner)
{
	if (GetAsyncKeyState(inner) & 0x8000) {
		PrevKey[inner] = 0x01;
		return true;
	}

	return false;
}

bool KeyModule::isKeyUp(int inner)
{
	if (!StayKeyDown(inner)) {
		if (PrevKey[inner] == 0x01) {
			PrevKey[inner] = 0;
			return true;
		}
	}

	return false;
}

bool KeyModule::ToggleKeyDown(int inner)
{
	if (GetKeyState(inner) & 0x0001) return true;
	return false;
}