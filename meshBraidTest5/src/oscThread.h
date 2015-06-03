#ifndef _OSC_THREAD
#define _OSC_THREAD

#include "ofMain.h"

class oscThread : of3dPrimitive {
    
public:
    void setup();
    void draw();
    void update();
    
    ofVec3f originP;
    ofVec3f destP;
    ofVec3f tempO; //temp origin
    ofVec3f tempD; //temp destination
    float length;
    float angleRotZ;
    //vector<float> offsetZ;
    
    ofColor color;
    
    int   res ;    //Resolution
    int   speed;  //Speed (lower=faster)
    float amp;    //Amplitude
    float f;      //Frequency
    
    int numVerts;
    
    oscThread(ofVec2f origin, ofMesh mesh);
};

#endif