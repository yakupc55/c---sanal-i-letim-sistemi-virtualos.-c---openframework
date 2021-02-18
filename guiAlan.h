#pragma once
#ifndef _GUIALAN
#define _GUIALAN
#include "ofMain.h"
class guiAlan
{
public:
	guiAlan();
	guiAlan(float X,float Y, float W, float H);
	float x, y;
	float witdh, height;
	bool active,click,keypress,runActive;
	int type, eventClickNO, specialId;
	void (*clickEvent)();
};

#endif