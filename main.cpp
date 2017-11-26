// Intro to openFrameworks
// by WILLPOWER STUDIOS / WILL ISMAEL http://willpowerstudios.com
// Rotating Sound Generative Cube Changing color based on Perlin Noise
// Some ideas inspired by https://github.com/junkiyoshi


#include "ofMain.h"
#include "ofVirtual.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1440,900,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofVirtual());
}
