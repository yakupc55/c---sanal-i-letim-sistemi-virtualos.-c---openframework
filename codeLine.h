#pragma once
#ifndef _CODELINE
#define _CODELINE
#include "ofMain.h"
class codeLine
{
public:
	codeLine();
	~codeLine();
	ofFbo fbo;
	static float lineSizeY,areaNumberSize,lineSizeX,fontSize;
	void setup();
	void drawNumber(int no);
	ofTrueTypeFont fonttext, fontnumber;
	int codeNumber;
	float lastLength,activeLength;
	string lineString;
};

#endif

