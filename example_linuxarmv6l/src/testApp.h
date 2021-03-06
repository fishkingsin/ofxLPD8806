#pragma once

#include "ofMain.h"
#include "ofxLEDsLPD8806.h"
#include "ofxLPD8806.h"
class testApp : public ofBaseApp , public ofThread{
	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void setPixels(std::vector<ofColor>colors);
		//--------------------------
		void threadedFunction();
//	ofxLEDsLPD8806 *led;
    ofxLEDsLPD8806 *led;
#ifdef TARGET_LINUX_ARM
	ofxLPD8806 spi;
#endif
	int mode;
	ofColor color;
	std::vector<ofColor>colors;
    std::vector<uint8_t>pixels;
	
};
