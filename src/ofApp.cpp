#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	setlocale(LC_CTYPE, "tr_TR.UTF-8");
	//std::setlocale(LC_CTYPE, ".UTF-8");
	cout << endl << "türkçe ğşıö";
	ofSetVerticalSync(false);
	vOs.setup();
	
}// setup sonu

//--------------------------------------------------------------
void ofApp::update(){
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
	vOs.update();
}// update sonu

//--------------------------------------------------------------
void ofApp::draw(){
	vOs.draw();
}// draw sonu

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	vOs.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	vOs.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	vOs.windowResized(w,h);
}// windowresized sonu

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
