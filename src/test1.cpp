#include "test1.h"

test1::test1() {


}



void test1::setup() {
	font.load("arial.ttf", 32);
	std::cout << "ilk çal??ma ba?ar?l?";
}// draw sonu

void test1::draw() {
	font.drawString("class test basarili",50,50);
}// draw sonu