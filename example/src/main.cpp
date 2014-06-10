#include "ofMain.h"
#ifdef TARGET_LINUX_ARM
#include "ofAppEGLWindow.h"
#endif
#include "testApp.h"

//========================================================================
int main( ){
#ifdef TARGET_LINUX_ARM
	ofAppEGLWindow::Settings settings;
    
	settings.eglWindowOpacity = 127;
    settings.frameBufferAttributes[EGL_DEPTH_SIZE]   = 0; // 0 bits for depth
    settings.frameBufferAttributes[EGL_STENCIL_SIZE] = 0; // 0 bits for stencil
    
	ofAppEGLWindow window(settings);
    
	ofSetupOpenGL(&window, 1024,768, OF_FULLSCREEN);// <-------- setup the GL context
#else
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
