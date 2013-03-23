#include "testApp.h"
const static int row = 16;
const static int col = 16;
const static int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;

//--------------------------------------------------------------
void testApp::setup(){
	player.loadMovie("Bad_Apple.mov");
	player.play();
	player.setPaused(false);
	player.setLoopState(OF_LOOP_NORMAL);
	ofSetWindowShape(player.getWidth()*2, player.getHeight());
	for (int i = 0 ; i < 256; i++)
	{
		GAMMA[i] = 0x80 | int(pow(float(i) / 255.0, 2.5) * 127.0 + 0.5);
	}
	

	
//	row = pixels[0].getHeight();
//	col = pixels[0].getWidth();
//	cout << pixels.back().getWidth() << " " <<pixels.back().getHeight() << endl;

//	numLED = row;

	ofSetFrameRate(25);
	ofSetLogLevel(OF_LOG_VERBOSE);


	if(spi.connect())
	{
		ofLogNotice()<<"connected to SPI";
	}
	else
	{
		ofLogNotice()<<"fails to connect SPI , sPI may not avaliable on your platform";
	}

//	colors = new vector<uint8_t>[1];
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors.push_back(255);
			colors.push_back(0);
			colors.push_back(0);
		}
		
	}
	colors.push_back(0);
	colors.push_back(0);
	startThread();
}
void testApp::exit()
{
	stopThread();	
	ofLogVerbose("spi")<< "close and clear led";
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
		
		colors [i] = GAMMA[0];
		colors [i+1] = GAMMA[0];
		colors [i+2] = GAMMA[0];
		}
	}


	spi.send(colors);

	
}
//--------------------------------------------------------------
void testApp::threadedFunction()
{
	while( isThreadRunning() != 0 ){
		if( lock() ){
			if(!lockPixel)
			{
//				for(int i = 0 ; i < col;i++)
				{
					spi.send(colors);
					usleep(1000);
				}
			}
			unlock();
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){
	player.update();
	lockPixel = true;
//	int frameIndex = ofGetFrameNum() % pixels.size();
	
	int sizeX = player.getWidth()/col;
	int sizeY = player.getHeight()/row;
	
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			
			int i2 = ((x*sizeX)+((y*sizeY)*col*sizeX))*3;
			unsigned char *pixels = player.getPixels();
			colors[i+1] = GAMMA[pixels[i2]];
			colors[i] = GAMMA[pixels[i2+1]];
			colors[i+2] = GAMMA[pixels[i2+2]];
		}
		
	}
	lockPixel = false;
}

//--------------------------------------------------------------
void testApp::draw(){
	player.draw(player.getWidth(), 0);
	#ifndef TARGET_LINUX_ARM
	int sizeX = player.getWidth()/col;
	int sizeY = player.getHeight()/row;
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			ofPushStyle();
			int i = (x+(y*col))*3;
			
			
			ofSetColor(colors [i+1], colors [i], colors [i+2]);
			ofRect((x)*sizeX,(y)*sizeY,sizeX,sizeY);
			ofPopStyle();
		}
	}
#endif
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