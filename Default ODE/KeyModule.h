#pragma once

class KeyModule
{
private:
	unsigned char  bKeyDown[256];
	unsigned char  PrevKey[256];

public:
	KeyModule();
	~KeyModule();

	bool isKeyDown(int inner);
	bool StayKeyDown(int inner);
	bool isKeyUp(int inner);
	bool ToggleKeyDown(int inner);

public:
	static KeyModule* Get()
	{
		static KeyModule Instance;
		return &Instance;
	}
};

