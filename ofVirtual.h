#pragma once

#include "ofMain.h"

class ofVirtual : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // cubes
        ofEasyCam cam;
        ofBoxPrimitive box;
        ofLight light;
    
        float noiseX, noiseY, noiseZ;
    
        int howBig;
    
    
        // mouse
        float moveX, moveY;
    
    
        // audio in
    
        void audioIn( float * input, int bufferSize, int nChannels );
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
    
        int bufferCounter;
        int drawCounter;
    
        float smoothedVol;
        float scaledVol;
        float amp;
    
        ofSoundStream soundStream;
		
};
