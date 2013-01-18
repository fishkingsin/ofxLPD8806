#include "ofMain.h"
#ifdef OF_TARGET_LINUXARMV6L
#include "ofGLES2Renderer.h"
#endif
#include "testApp.h"

//========================================================================
int main( ){
#ifdef OF_TARGET_LINUXARMV6L
	ofGLES2Renderer * renderer = new ofGLES2Renderer();
	ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(renderer));
#endif
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
