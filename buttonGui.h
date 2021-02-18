#pragma once
#ifndef _BUTTONGUI
#define _BUTTONGUI
#include "ofMain.h"
#include "guiAlan.h"
class buttonGui
{
public:
	buttonGui();
	void draw(float Mx,float My);
	void imgCreate();
	guiAlan* alan;
	std::string imgYolaktiv,imgYoldeaktiv,name;
	ofColor color;
	bool imgYolB, nameB, colorB;
	ofFbo button;
	ofImage img;

};


#endif
