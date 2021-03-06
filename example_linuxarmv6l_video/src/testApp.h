#pragma once

#include "ofMain.h"
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
	
		//--------------------------
		void threadedFunction();

	ofxLPD8806 spi;

//    vector <ofPixels> pixels;
	
	vector<uint8_t> colors;
	
	u_int8_t GAMMA[256];
	bool lockPixel;
	ofVideoPlayer player;
};
