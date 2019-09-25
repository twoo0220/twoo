#pragma once
#pragma comment (lib, "drawstuff.lib")
#pragma comment (lib, "ode_doubled.lib")

#include <ode.h>
#include <drawstuff.h>
#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#define dsDrawBox dsDrawBoxD
#define dsDrawCapsule dsDrawCapsuleD
#endif // dDOUBLE

#include <Windows.h>
#include <iostream>
#include <assert.h>					// File Found check

#include <stdlib.h>					// Random Position Function
#include <math.h>					// Random Position Function

#include "KeyModule.h"

#define KeyCode KeyModule::Get()
#define COUNT_MAX 50				// Prey, Predator maximum count