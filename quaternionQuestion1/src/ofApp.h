#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        float length;
        ofVec3f tempO, tempD;
        ofVec3f originP, destP;
        float angleRotX, angleRotY, angleRotZ;
        ofQuaternion roll, yaw, pitch, curRot;
        ofMesh targets;
        ofMesh connections;
        ofEasyCam cam;
		
};
