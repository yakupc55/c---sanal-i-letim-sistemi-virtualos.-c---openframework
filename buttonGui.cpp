#include "buttonGui.h"


buttonGui::buttonGui() {
	
}

void buttonGui::draw(float Mx,float My)
{
	button.begin();
	img.draw(0,0, alan->witdh, alan->height);
	button.end();
	button.draw(alan->x*Mx,alan->y*My,alan->witdh*Mx,alan->height*My);
}

void buttonGui::imgCreate()
{
	img.loadImage(imgYolaktiv);
	button.allocate(alan->witdh,alan->height);
	button.begin();
	if (imgYolB) {
		img.draw(0,0,alan->witdh,alan->height);
	}
	
	if (colorB) {

	}
	if (nameB) {

	}
	button.end();
}// fonksiyon sonu

