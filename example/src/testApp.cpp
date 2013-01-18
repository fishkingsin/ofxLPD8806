#include "testApp.h"
int row = 10;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;
//unsigned char *gamma;
ofColor color;
//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	led = new ofxLEDsLPD8806(numLED);
	for(int i = 0 ; i< numLED ; i++)
	{
		float x = 50+20+(i%col)*ptSize;
		float y = 100+20+(i/col)*ptSize;
		led->addLED(i,ofVec2f(x,y));
	}
	spi.connect();
//	gamma = new unsigned char[256];
//	for (i = 0 ; i < 256;i++)
//	{
//		int shift = powf((i*1.0f) / 255.0, 2.5) * 127.0 + 0.5;
//		gamma[i] = (0x80 | shift)-127;
//	}
}
void testApp::exit()
{
	ofLogVerbose("spi")<< "close and clear led";
	led->clear(0);
	spi.send(led->txBuffer);
}
//--------------------------------------------------------------
void testApp::update(){
//	led->clear(0);
//	led->clear(ofColor::black);
//	led->renderBuffer.begin();
//	
//	//draw video as 8px width,height
//	//draw line by line horizontally
//	//[8 px first row ][8 px second row ]
//	ofPushStyle();
//	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//	
//	for(int i = 0 ; i < 1; i++)
//	{
//		ofSetColor(ofColor::fromHsb(i%360, 255, 255),200);
//		ofCircle(int(ofGetFrameNum()+i*(SQAURE_ROOT)-16)%numLED, 0, SQAURE_ROOT*0.5);
//	}
//	ofDisableBlendMode();
//	ofPopStyle();
//	led->renderBuffer.end();
//
//	led->encode();
	color.r = counter;
	color.g = counter;
	color.b = counter;
	led->clear(color);

	spi.send(led->txBuffer);
	counter++;
	counter%=255;
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(color);
//	ofPushStyle();
//	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//	
//	for(int i = 0 ; i < 1; i++)
//	{
//		ofSetColor(ofColor::fromHsb(i%360, 255, 255),200);
//		ofCircle(int(ofGetFrameNum()+i*(SQAURE_ROOT)-16)%numLED, 0, SQAURE_ROOT*0.5);
//	}
//	ofDisableBlendMode();
//	ofPopStyle();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}