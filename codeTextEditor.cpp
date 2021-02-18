#include "codeTextEditor.h"

codeTextEditor::codeTextEditor()
{

}//fonksiyon sonu

codeTextEditor::~codeTextEditor()
{

}//fonksiyon sonu

void codeTextEditor::draw(float Mx, float My)
{
	fbo.begin();
	documentList[activeDocument].draw(Mx, My, alan->runActive);
	fbo.end();
	fbo.draw(alan->x * Mx, alan->y * My, alan->witdh * Mx, alan->height * My);
	
}//fonksiyon sonu

void codeTextEditor::clikc(int x, int y, int button)
{
	konum = (y - alan->y) / lineSize;
	int t = (y - alan->y) / lineSize;
	documentList[activeDocument].clikc(x,y,button,konum);
}//fonksiyon sonu

void codeTextEditor::keypressed(int key)
{
	documentList[activeDocument].keypressed(key);
}//fonksiyon sonu

void codeTextEditor::setup()
{
	/*
	activeLine = 0;
	lineSize = 16;
		addlines();
		*/
	activeDocument = 0;
	lineSize = 16;
	fontSize = 12;
	codeDocument add = codeDocument();
	add.setup(lineSize,fontSize);
	codeDocument add2 = codeDocument();
	add2.setup(lineSize, fontSize);
	//draw için ilk ekleme
	documentList.push_back(add);

	//setup için ilk ekleme
	documentList.push_back(add2);
}//fonksiyon sonu






