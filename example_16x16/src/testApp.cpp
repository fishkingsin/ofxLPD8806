#include "testApp.h"
int row = 16;
int col = 16;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
static int counter = 0;

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(24);
	ofSetLogLevel(OF_LOG_VERBOSE);

	for (int i = 0 ; i < 256; i++)
	{
		GAMMA[i] = 0x80 | int(pow(float(i) / 255.0, 2.5) * 127.0 + 0.5);
	}
	
	ofDirectory dir;
    dir.allowExt("jpg");
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
	
	numLED = row*col;

	
#ifdef TARGET_LINUX_ARM
	if(spi.connect())
	{
		ofLogNotice()<<"connected to SPI";
	}
	else
	{
		ofLogError()<<"Fail to connect SPI";
	}
#endif

	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors.push_back(GAMMA[pixels[0][i+1]]);
			colors.push_back(GAMMA[pixels[0][i]]);
			colors.push_back(GAMMA[pixels[0][i+2]]);
		}
		colors.push_back(0);
		colors.push_back(0);
	}
	
	startThread(false,false);
	mode = 0;
	tex.allocate(col,row,GL_RGB);
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
			colors[i+1] = GAMMA[0];
			colors[i] = GAMMA[0];
			colors[i+2] = GAMMA[0];
		}
		
	}
#ifdef TARGET_LINUX_ARM
	spi.send(colors);
#endif
}
//--------------------------------------------------------------
void testApp::threadedFunction()
{
	while( isThreadRunning() != 0 ){
		if( lock() ){
			
			if(!lockPixel)
			{
				for(int i = 0 ; i < col;i++)
				{
#ifdef TARGET_LINUX_ARM

					spi.send(colors);
#endif
					usleep(1000);
				}
			}



			
			unlock();
			usleep(10000);
		}
	}
}
//--------------------------------------------------------------
void testApp::update(){
	lockPixel = true;
	counter++;
	int frameIndex = counter % pixels.size();
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			colors[i+1] = GAMMA[pixels[frameIndex].getPixels()[i]];
			colors[i] = GAMMA[pixels[frameIndex].getPixels()[i+1]];
			colors[i+2] = GAMMA[pixels[frameIndex].getPixels()[i+2]];
		}
		
	}
	tex.loadData(pixels[frameIndex].getPixels(), col, row, GL_RGB);
	lockPixel = false;
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(125);
	int SIZE = ofGetWidth()/64;
	for(int x = 0 ; x < col ; x++)
	{
		for(int y = 0 ; y < row ; y++)
		{
			int i = (x+(y*col))*3;
			
		
			ofSetColor(colors[i+1],colors[i],colors[i+2]);
			ofRect(x*SIZE,y*SIZE,SIZE-1,SIZE-1);
		}
	}
	ofSetColor(255);
	tex.draw(0,0);
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
