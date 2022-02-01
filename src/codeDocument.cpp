#include "codeDocument.h"

codeDocument::codeDocument()
{

}//fonksiyon sonu

codeDocument::~codeDocument()
{

}//fonksiyon sonu

void codeDocument::setup(int line,float fSize)
{
	activeLine = 0;
	lineSize = line;
	fontSize = fSize;
	addlines();

	ofTrueTypeFontSettings setting("arial.ttf", fontSize);
	setting.addRanges(ofAlphabet::Latin);
	font.load(setting);
	startTextX = 50;

	spacingWeight =fontSize/2;
}//fonksiyon sonu



void codeDocument::draw(float Mx, float My,bool runActive)
{
	ofBackground(255);
	//linesları düz mantık olarak listeliyoruz.
//	cout << endl << "lines uzunlugu : " << lines.size();
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i].fbo.draw(0, i * lineSize);
	}// for sonu

	if (runActive) {
		if (ofGetElapsedTimeMillis() % 800 <= 500) {
			ofSetColor(0);
			ofDrawLine(startTextX + lines[activeLine].activeLength, 0 + (activeLine * lineSize), startTextX+ lines[activeLine].activeLength, 16 + (activeLine * lineSize));
		}// süre sistemli yapı
	}//if sonu

}//fonksiyon sonu


void codeDocument::clikc(int x, int y, int button,int konum)
{
	if (lines.size() <= konum) {
		activeLine = lines.size() - 1;
	}// if sonu
	else {
		activeLine = konum;
	}// else sonu
}//fonksiyon sonu

void codeDocument::keypressed(int key)
{
	if (key >= 0 && key <= 32) {
		switch (key) {
			// enter tuşuna basılırsa
		case 13:
			// test sürümünde sayfa boyunu geçmemesi sağlandı.
			if (lines.size() <= 32) {
				addlines(activeLine + 1);
				activeLine++;
			}// if sonu
			break;

			// silme tuşuna basılırsa
		case 8:

			if (activeLine > 0) {
				if (lines[activeLine].lineString.length() == 0) {
					deletelines(activeLine);
					activeLine--;
				}// boş string kontrol ifi
			}// en dip kontrol ifi

			break;

			//bosluk karekteri
		case 32:
		pressedSpace();
		break;
		}// switch sonu
	}// ilk keylerin sonu

	if (key >= 32 && key <= 512) {
	//	cout << endl << "key calisma kismi";
		drawString(key);
	}// harflerin bulunduğu alan sonu
}//fonksiyon sonu

void codeDocument::addlines()
{
	codeLine line;
	lines.push_back(line);
	lines[lines.size() - 1].codeNumber = lines.size();
	lines[lines.size() - 1].setup();
}//fonksiyon sonu

void codeDocument::addlines(int no)
{
	codeLine line;
	lines.insert(lines.begin() + no, line);
	lines[no].codeNumber = no + 1;
	lines[no].setup();
	
	if (lines.size() != no) {
		changesLines(no + 1);
	}//if sonu
}//fonksiyon sonu

void codeDocument::deletelines(int no)
{
	lines.erase(lines.begin() + no);
	if (lines.size() != no) {
		changesLines(no);
	}//if sonu
}//fonksiyon sonu

void codeDocument::changesLines(int no)
{
	int a = 0;
	for (int i = no; i < lines.size(); i++)
	{
		a++;
		lines[i].drawNumber(i + 1);
	}// for sonu
}//fonksiyon sonu

void codeDocument::drawString(int key)
{
	string a;
	ofUTF8Append(a, key);;
	cout << endl << "yapilan string dönüşümü : " << a;
	float uzunluk = font.stringWidth(a);
	ofFbo* fbo = &lines[activeLine].fbo;
	fbo->begin();

//	ofBackground(128);
	ofSetColor(0, 0, 0, 255);
	font.drawString(a,50+ lines[activeLine].lastLength,fontSize+1);
	fbo->end();

	lines[activeLine].lineString +=a;
	lines[activeLine].lastLength += uzunluk;
	lines[activeLine].activeLength = lines[activeLine].lastLength;
}//fonksiyon sonu

void codeDocument::pressedSpace()
{
	lines[activeLine].lastLength += spacingWeight;
	lines[activeLine].lineString += " ";
	lines[activeLine].activeLength = lines[activeLine].lastLength;
}//fonksiyon sonu


