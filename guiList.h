#pragma once
#ifndef _GUILIST
#define _GUILIST
#include "ofMain.h"
#include "guiAlan.h"
class guiList
{
public:
	int type;
	int specialId;
	guiList();
	guiList(int t, int s);
	guiList(int t, int s , guiAlan *a);
	~guiList();

	guiAlan* alan;
};

#endif