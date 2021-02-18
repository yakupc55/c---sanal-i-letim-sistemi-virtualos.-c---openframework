#include "codeLine.h"
float codeLine::areaNumberSize = 48;
float codeLine::lineSizeY = 16;
float codeLine::lineSizeX = 480;
float codeLine::fontSize = 10;
codeLine::codeLine()
{

}//fonksiyon sonu

codeLine::~codeLine()
{

}//fonksiyon sonu

void codeLine::setup()
{
	fontnumber.load("font\\codenumber.ttf", fontSize);
	fbo.allocate(lineSizeX, lineSizeY);
	fbo.begin();
	ofBackground(255);

	//numaralandırma alanının çizimi
	ofSetColor(165, 145, 132);
	ofDrawRectangle(0, 0, areaNumberSize, lineSizeY);

	//numaranın yazılması işlemi
	ofSetColor(0, 89, 78);
//	cout << endl << "uzunluk denemesi " << fontnumber.stringWidth("bu bir deneme");
	fontnumber.drawString(ofToString(codeNumber), 10, 14);
	fbo.end();
	lineString = "";
	lastLength = 0;
	activeLength = 0;
}//fonksiyon sonu

void codeLine::drawNumber(int no)
{
	fbo.begin();

	//numaralandırma alanının çizimi
	ofSetColor(165, 145, 132);
	ofDrawRectangle(0, 0, areaNumberSize, lineSizeY);

	//numaranın yazılması işlemi
	ofSetColor(0, 89, 78);
	fontnumber.drawString(ofToString(no), 10, 14);

	fbo.end();

	codeNumber = no;
}//fonksiyon sonu


