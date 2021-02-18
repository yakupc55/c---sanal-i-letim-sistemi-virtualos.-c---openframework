#pragma once
#ifndef _PROGRAM
#define _PROGRAM
#include "ofMain.h"
#include "buttonGui.h"
#include "guiList.h"
#include "guiAlan.h"
#include "codeTextEditor.h"
class program
{
public:
	program();
	~program();
	ofFbo	fbo;
	ofImage img,minImg;
	vector<guiList*> guiListesi;
	vector<buttonGui*> buttonGuiList;
	vector<codeTextEditor*> textEditorList;
	// tüm programlar prototip sürümünde aynı noktada başladıkları için
	// bu kisim statik olarak eklenmiştir. 
	static float addMainX, addMainY;
	void (*setup)();
	void (*draw)();
	void addGuiParametres(buttonGui* button, guiAlan* alan);
	void addGuiParametres(codeTextEditor* textCode, guiAlan* alan);
	void drawGui(float MainXt,float MainYt);
	void mousePressed(int x, int y, int button, float MainX, float MainY);
	void keyPressed(int key);
	int searchIdbutton(int id);
	int searchIdtextCode(int id);
	bool tarama(guiAlan alan, int x, int y, float MainX, float MainY);
	int specialIdSayac, lastProgram, programCode,activeGui,lastActiveGui;
	bool runProgram, openProgram,desktopProgram = false;
	string programName;
};

#endif
