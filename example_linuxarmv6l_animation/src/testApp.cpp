#include "testApp.h"
int row = 1;
int col = 32;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
int counter = 0;

//--------------------------------------------------------------
void testApp::setup(){
	
	for (int i = 0 ; i < 256; i++)
	{
		GAMMA[i] = 0x80 | int(pow(float(i) / 255.0, 2.5) * 127.0 + 0.5);
	}
	
	ofDirectory dir;
    
    int nFiles = dir.listDir("plops");
	pixels.assign(nFiles,ofPixels());
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) {
            
            // add the image to the vector
            string filePath = dir.getPath(i);
			ofImage img;
			img.loadImage(filePath);
			img.setImageType(OF_IMAGE_COLOR);

			pixels[i].allocate(img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);
			pixels[i].setFromPixels(img.getPixels() ,img.getWidth(), img.getHeight(),3) ;
            
        }
        
    }
    else printf("Could not find folder\n");

	
	row = pixels[0].getHeight();
	col = pixels[0].getWidth();
	cout << pixels.back().getWidth() << " " <<pixels.back().getHeight() << endl;

	numLED = row;

	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);


	if(spi.connect())
	{
		ofLogNotice()<<"connected to SPI";
	}
	else
	{
		ofLogNotice()<<"fails to connect SPI , sPI may not avaliable on your platform";
	}


	colors = new vector<uint8_t>[col];
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors[x].push_back(GAMMA[pixels.back()[i+1]]);
			colors[x].push_back(GAMMA[pixels.back()[i]]);
			colors[x].push_back(GAMMA[pixels.back()[i+2]]);
		}
		colors[x].push_back(0);
		colors[x].push_back(0);
	}
	
	startThread();
}
void testApp::exit()
{
	stopThread();
	ofLogVerbose("spi")<< "close and clear led";
	for(int y = 0 ; y < row ; y++)
	{
		
		colors[0][y*3] = GAMMA[0];
		colors[0][y*3+1] = GAMMA[0];
		colors[0][y*3+2] = GAMMA[0];
	}


	spi.send(colors[0]);

	
}
//--------------------------------------------------------------
void testApp::threadedFunction()
{
	while( isThreadRunning() != 0 ){
		if( lock() ){
			
			for(int i = 0 ; i < col;i++)
			{
				spi.send(colors[i]);
				usleep(1000);
			}
			unlock();
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){
	int frameIndex = ofGetFrameNum() % pixels.size();
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors[x][y*3+1] = GAMMA[pixels[frameIndex][i]];
			colors[x][y*3] = GAMMA[pixels[frameIndex][i+1]];
			colors[x][y*3+2] = GAMMA[pixels[frameIndex][i+2]];
		}
		
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	#ifndef TARGET_LINUX_ARM
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			ofPushStyle();
			int i = y*3;
			ofSetColor(colors[x][i+1], colors[x][i], colors[x][i+2]);
			ofRect((x)*5+20,20+(y)*5,4,4);
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