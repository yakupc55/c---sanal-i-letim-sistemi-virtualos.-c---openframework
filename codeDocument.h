#pragma once
#ifndef _CODEDOCUMENT
#define _CODEDOCUMENT
#include "ofMain.h"
#include "codeLine.h"

class codeDocument
{
public:
	codeDocument();
	~codeDocument();
	void setup(int lineSize,float fSize);
	vector<codeLine> lines;
	void draw(float Mx, float My,bool runActive);
	void clikc(int x, int y, int button,int konum);
	void keypressed(int key);
public:
	void addlines();
	void addlines(int no);
	void deletelines(int no);
	void changesLines(int no);
	void drawString(int key);
	void pressedSpace();
	float lineSize, fontSize,startTextX;
	int activeLine;
	ofTrueTypeFont font;
	float spacingWeight;
};// sınıf sonu

#endif