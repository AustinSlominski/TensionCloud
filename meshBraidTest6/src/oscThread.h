#ifndef _OSC_THREAD
#define _OSC_THREAD

#include "ofMain.h"

class oscThread : of3dPrimitive {
    
public:
    void setup();
    void draw();
    void update();
    
    ofVec3f originP, destP;
    ofVec3f tempO, tempD; //temp origin/dest
    float length;
    float angleRotX, angleRotY, angleRotZ;
    ofQuaternion roll, yaw, pitch, curRot;
    
    ofColor color;
    
    int   res ;    //Resolution
    int   speed;  //Speed (lower=faster)
    float amp;    //Amplitude
    float f;      //Frequency
    
    int numVerts;
    
    oscThread(ofVec2f origin, ofMesh mesh);
};

#endif