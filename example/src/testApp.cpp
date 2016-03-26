#include "testApp.h"
int row = 10;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;

ofColor color;
void drawGraphic(int mode)
{
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	for(int i = 0 ; i < 1; i++)
	{
		ofSetColor(ofColor::fromHsb(i%360, 255, 255),200);
		ofDrawCircle(int(ofGetFrameNum()+i*(SQAURE_ROOT)-16)%numLED, 0, SQAURE_ROOT*0.5);
	}
	ofDisableBlendMode();
	ofPopStyle();
	
}
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
#ifdef TARGET_LINUX_ARM
	spi.connect();
	ofLogNotice()<<"connected to SPI";
#endif
	
}
void testApp::exit()
{
	ofLogVerbose("spi")<< "close and clear led";
	led->clear(0);
#ifdef TARGET_LINUX_ARM
	spi.send(led->txBuffer);
#endif
}
//--------------------------------------------------------------
void testApp::update(){
	led->clear(0);
	led->clear(ofColor::black);
	led->renderBuffer.begin();
	
	//draw video as 8px width,height
	//draw line by line horizontally
	//[8 px first row ][8 px second row ]
	drawGraphic(0);
	led->renderBuffer.end();
	


#ifdef TARGET_LINUX_ARM
	spi.send(led->txBuffer);
#endif
	counter++;
	counter%=255;
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(ofColor::gray);
	
	
	
	ofPushMatrix();
	ofScale(10, 10);
	//draw again to preview
	drawGraphic(0);
	//	led->encodedBuffer.draw(0,0);
	ofPopMatrix();
	
	ofPushStyle();
	ofNoFill();
	ofSetColor(0, 255, 0);
	ofRect(0,0,numLED*10,10);
	ofPopStyle();
	
	led->draw();
	
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