#include "testApp.h"
int row = 2;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;



//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	led = new ofxLEDsLPD8806(numLED);
//	for(int i = 0 ; i< numLED ; i++)
//	{
//		float x = 50+20+(i%col)*ptSize;
//		float y = 100+20+(i/col)*ptSize;
//		led->addLED(i,ofVec2f(x,y));
//	}

	if(	spi.connect())
	{
		ofLogNotice()<<"connected to SPI";
	}

	colors.assign(numLED,ofColor());
	startThread(false,false);
	mode = 0;
}
void testApp::exit()
{
	stopThread();
	ofLogVerbose("spi")<< "close and clear led";
	led->clear(0);

	spi.send(led->txBuffer);

}
//--------------------------------------------------------------
void testApp::threadedFunction()
{
	while( isThreadRunning() != 0 ){
		if( lock() ){
			
			led->setPixels(colors);

			spi.send(led->txBuffer);

			
			unlock();
			usleep(10000);
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){

	if(ofGetFrameNum()%200==0)
	{
		#ifdef TARGET_LINUX_ARM
		mode++;
		mode%=10;
		#endif


		
		
	}

	
	if(mode==0)
	{
		for(int i =0 ; i < colors.size(); i++)
		{
			if(i==counter)colors[i] = ofColor(255,0,0);
			else colors[i] = ofColor::black;
			
		}
	}
	else if (mode==1)
	{
		for(int i =0 ; i < colors.size(); i++)
		{
			if(i==counter)colors[i] = ofColor(0,255,0);
			else colors[i] = ofColor::black;
			
		}
	}
	else if (mode==2)
	{
		for(int i =0 ; i < colors.size(); i++)
		{
			if(i==counter)colors[i] = ofColor(0,0,255);
			else colors[i] = ofColor::black;
			
		}
	}
	else if (mode==3)
	{
		for(int i =0 ; i < colors.size(); i++)
		{
			float h = (((i+counter)%colors.size()*1.0f)/colors.size());
			colors[i] = ofColor::fromHsb(255*h, 256, 256);
			
		}
	}
	else if (mode==4)
	{
		for(int i =0 ; i < colors.size(); i++)
		{
			
			float h = sinf((((i+counter*1.0f)/colors.size())*TWO_PI))+1;
			colors[i] = ofColor::fromHsb(ofGetFrameNum()%255, 125*h, 255);
			
		}
	}
	else if (mode==5)//breath
	{
		float h = sinf((ofGetElapsedTimef()*0.1)*TWO_PI)+1;
		for(int i =0 ; i < colors.size(); i++)
		{
			

			colors[i] = ofColor(125*h);
			
		}
	}
	counter++;
	counter%=colors.size();
    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(125);
	int SIZE = ofGetWidth()/32;
	for(int i =0 ; i < colors.size(); i++)
	{
		ofSetColor(colors[i]);
		ofRect((i%32)*SIZE,(i/32)*SIZE,SIZE-1,SIZE-1);
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key>='0' || key <= '9')
	{
		mode = key-'0';
	}
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