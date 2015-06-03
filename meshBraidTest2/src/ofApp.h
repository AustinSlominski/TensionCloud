#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
    public:
        void setup();
        void update();
        void draw();
        
        void keyPressed(int key);
        void sendWave(int index,int burst);
        void updateWave(int i);
        
        int oscNum;
        
        ofMesh mesh;
        //vector< vector<of3dPrimitive> > oscMesh;
        vector<of3dPrimitive> oscMesh;
        ofEasyCam cam;
        
        float time;
    
    float speed = 5;
    float amp = 10;
    float f = 10;
};
