#ifndef STDAFX_H
#define STDAFX_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <Windows.h>
#include "exceptionMacros.h"
#include "freeglut.h"
#include "Point2D.h"
#include "Point3D.h"
#include "typeDefinitions.h"
#include "al.h"
#include "alc.h"

//Prototypes

void ALBuffer(void);
int ALInit(void);
void changeSource(void);
int setUpAudio(void);
void ALchangeGain(float front, float left, float back, float right);

//End of OpenAL

using namespace std;

#endif