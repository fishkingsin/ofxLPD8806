#include "testApp.h"
int row = 1;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;
ofColor color;
vector<uint8_t> *colors;

//u_int8_t GAMMA[256];
//--------------------------------------------------------------
void testApp::setup(){
	
//	for (int i = 0 ; i < 256; i++)
//	{
////		int shift = powf((i*1.0f) / 255.0, 2.5) * 127.0 ;
//		GAMMA[i] = (i >> 1)+1;
//	}
	image.loadImage("image.png");
	
	row = image.getHeight();
	col = image.getWidth();
	numLED = row;

	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	led = new ofxLEDsLPD8806(numLED);
	for(int i = 0 ; i< numLED ; i++)
	{
		float x = 50+20+(i%col)*ptSize;
		float y = 100+20+(i/col)*ptSize;
		led->addLED(i,ofVec2f(x,y));
	}
#ifdef TARGET_LINUX_ARM
	if(spi.connect())
	{
		ofLogNotice()<<"connected to SPI";
	}
	else
	{
		ofLogNotice()<<"fails to connect SPI";
	}
#endif

	colors = new vector<uint8_t>[col];
	
	unsigned char *pixels = image.getPixels();


	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors[x].push_back(pixels[i]);
			colors[x].push_back(pixels[i+1]);
			colors[x].push_back(pixels[i+2]);
		}
		colors[x].push_back(0);
	}
	
	startThread();
}
void testApp::exit()
{
	stopThread();
	ofLogVerbose("spi")<< "close and clear led";
	led->clear(0);
#ifdef TARGET_LINUX_ARM
	spi.send(led->txBuffer);
#endif
	
}
//--------------------------------------------------------------
void testApp::threadedFunction()
{
	while( isThreadRunning() != 0 ){
		if( lock() ){
			
			led->setPixels(colors[counter].data(),row);
//			for(int i=0 ; i < led->txBuffer.size() ; i++)
//			{
//				cout << int(led->txBuffer[i]) << "\t";
//			}
#ifdef TARGET_LINUX_ARM
			spi.send(led->txBuffer);
#endif
			counter++;
			counter%=col;
			unlock();
			usleep(100000);
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	image.draw(0,0);
	
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
		ofPushStyle();
		ofSetColor((int)colors[x][y*3], (int)colors[x][y*3+1], (int)colors[x][y*3+2]);
		ofRect((x)*10,image.getHeight()+(y)*10,10,10);
		ofPopStyle();
		}
	}
	
	for(int y = 0 ; y < row ; y++)
	{
		ofPushStyle();
		ofSetColor((int)led->txBuffer[y*3], (int)led->txBuffer[y*3+1], (int)led->txBuffer[y*3+2]);
		ofRect((y)*10,ofGetHeight()-20,10,10);
		ofPopStyle();
	}
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