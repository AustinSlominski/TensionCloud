#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    float length;
    ofVec3f tempO, tempD;
    ofVec3f originP, destP;
    float angleRotX, angleRotY, angleRotZ;
    ofQuaternion roll, yaw, pitch, curRot;
    ofMesh targets;
    ofMesh connections;
    ofEasyCam cam;
  
    ofColor curColor;
    
    float speed;
    int cc;
};
