#include "ofVirtual.h"

//--------------------------------------------------------------
void ofVirtual::setup(){
    
    // basics
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    ofSetWindowTitle("Virtual Hexahedron");
    
    // Let's get Virtual
    ofSetLineWidth(1);
    ofSetColor(ofColor(255, 0, 0));
    
    this->noiseX = ofRandom(10);
    this->noiseY = ofRandom(10);
    this->noiseZ = ofRandom(10);
    
    this->light.setAreaLight(2048, 2048);
    this->light.setAmbientColor(ofFloatColor(0.0, 0.0, 0.0, 1.0));
    this->light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    this->light.setSpecularColor(ofFloatColor(1.0, 0.0, 0.0));
    
    howBig = ofRandom(125,175);
    
    
    // audio in
    
    soundStream.printDeviceList();
    
    // if you want to set a different device id
    // soundStream.setDeviceID(0);
    // bear in mind the device id corresponds to all audio devices, including input-only and output-only.
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400,0.0);
    
    bufferCounter   = 0;
    drawCounter     = 0;
    smoothedVol     = 0.0;
    scaledVol       = 0.0;
    
    // output channels,
    // 2 input channels,
    // 44100 samples per sec
    // 256 samples per buffer
    // 4 num buggers (latency)
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    
    
}

//--------------------------------------------------------------
void ofVirtual::update(){
    // audio in
    // lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, .03, .0, 1.0,true);
    
    // lets record the vol in an array
    volHistory.push_back( scaledVol );
    
    // if we are bigger then the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ) {
        volHistory.erase(volHistory.begin(),volHistory.begin()+1);
    }
}

//--------------------------------------------------------------
void ofVirtual::draw(){
    amp = scaledVol * 500.0f;
    
    cam.begin();
    // ofRotateZ(180);
    this->light.setPosition(this->cam.getPosition().normalize() * 2048);
    ofEnableLighting();
    this->light.enable();
    
    float tmp_noiseX = this->noiseX;
    float tmp_noiseY = this->noiseY;
    float tmp_noiseZ = this->noiseZ;
    
    float x_span = ofGetWidth() / 6;
    float angle = 0;
    
    float n_x = ofNoise(tmp_noiseX);
    float n_y = ofNoise(tmp_noiseY);
    float n_z = ofNoise(tmp_noiseZ);
    
    ofColor WarriorLight;
    WarriorLight.setHsb(( n_x + n_y + n_z ) / 2 * 255, 175, 175);
    ofSetColor(WarriorLight);
    
    //moveX = ofGetWidth() / 25;
    //moveY = ofGetHeight() / 25;
    
    ofPushMatrix();
    //ofTranslate(ofVec3f( moveX, moveY, 0 ));
    ofTranslate(moveX, moveY, 10*amp);
    ofRotateX(360 * n_x);
    ofRotateY(360 * n_y);
    ofRotateZ(360 * n_z);
    box.set(howBig);
    box.draw();
    box.enableColors();
    ofPopMatrix();
    
    tmp_noiseX -= .05;
    tmp_noiseY += .05;
    tmp_noiseZ += .05;
    
    this->noiseX += .015;
    this->noiseY += .015;
    this->noiseZ += .015;
    
    cam.end();
}

//--------------------------------------------------------------
void ofVirtual::audioIn( float * input, int bufferSize, int nChannels ){
    float curVol = 0.0;
    
    // samples are interleaved
    int numCounted = 0;
    
    // lets go through each sample and calculate the root mean square which is a rough way to calculate vol
    for ( int i = 0; i < bufferSize; i++ ) {
        left[i]     = input[i*2]*.5;
        right[i]    = input[i*2+1]*.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted += 2;
    }
    
    // this is how we get the mean of rms ;)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= .83;
    smoothedVol += .07 * curVol;
    
    bufferCounter++;
}

//--------------------------------------------------------------
void ofVirtual::keyPressed(int key){
    
    // SOUND //
    
    if( key == 's' ) {
        soundStream.start();
    }
    
    if ( key == 'e' ) {
        soundStream.stop();
    }
}

//--------------------------------------------------------------
void ofVirtual::keyReleased(int key){

}

//--------------------------------------------------------------
void ofVirtual::mouseMoved(int x, int y ){
    moveX = x/5;
    moveY = -y/5;
}

//--------------------------------------------------------------
void ofVirtual::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofVirtual::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofVirtual::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofVirtual::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofVirtual::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofVirtual::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofVirtual::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofVirtual::dragEvent(ofDragInfo dragInfo){ 

}
