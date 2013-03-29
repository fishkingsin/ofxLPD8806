#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxImageSequence.h"
#include "ofxXmlSettings.h"
#include "ofxLPD8806.h"
#include "ofxLEDsLPD8806.h"
class testApp : public ofBaseApp  {//, public ofThread{
    
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //tcp
    ofxTCPClient client;
    bool weConnected;
    float connectTime , deltaTime ;
    string host;
    int port;
    
    //image sequence
    vector<ofxImageSequence*> sequences;
    
    //led
    //--------------------------
//    void threadedFunction();
	ofxLEDsLPD8806 *led;
    
	ofxLPD8806 spi;
    
	int mode;
//	ofColor color;
//	std::vector<ofColor>colors;
    int numLED;
    
};
