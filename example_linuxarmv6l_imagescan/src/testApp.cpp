#include "testApp.h"
int row = 1;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;
ofColor color;
unsigned char *colors;


//--------------------------------------------------------------
void testApp::setup(){
	image.loadImage("image.png");
	
	row = image.getHeight();
	col = image.getWidth();
	numLED = col;

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

	colors = new unsigned char[row*col*3];
	unsigned char *pixels = image.getPixels();
	for(int x = 0 ; x < col ; x++)
	{

		for(int y = 0 ; y < row ; y++)
		{
			int i = y+x*row;
			colors[i] = pixels[i];
		}
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
			
			led->setPixels(&colors[counter],row);
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
			usleep(100);
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
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