#pragma once

#include "ofMain.h"
#include "oscThread.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int numMesh;
    
    ofEasyCam cam;
    ofMesh mesh;
    vector< vector<oscThread> > braid;
    vector<ofVec3f> offsets;
    
    ofParameter<float> amp, f;
    ofParameter<int> res, speed;
    
    ofxPanel gui;
};
