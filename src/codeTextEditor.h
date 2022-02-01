#pragma once
#ifndef _CODETEXTEDITOR
#define _CODETEXTEDITOR
#include "ofMain.h"
#include "guiAlan.h"
#include "codeLine.h"
#include "codeDocument.h"

class codeTextEditor
{
public:
	codeTextEditor();
	~codeTextEditor();
	void setup();
	void draw(float Mx, float My);
	void clikc(int x,int y,int button);
	void keypressed(int key);
	guiAlan* alan;
	ofFbo fbo;
	int activeDocument;
private:
	float lineSize, fontSize;
	int second,konum;
	vector <codeDocument> documentList;
};
#endif
