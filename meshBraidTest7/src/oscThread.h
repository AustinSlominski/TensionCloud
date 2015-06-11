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
    ofVec3f rotationAngle, direction, axis;
    ofQuaternion rotation;
    float time;
    float length;
    float rotationAmount;
    
    int color;
    int numVerts;
    
    //Braid Construction
        float mTime;  //Modulation Time
        int   res;    //Resolution
        int   speed;  //Speed (lower=faster)
        float amp;    //Amplitude
        float f;      //Frequency
    
    //Lead and Tail Construction / Movement
        float tcTime, cSpeed;        //Actual speed of movement
        int   cTime, tC, ttLength, tLength; //Tail Control Data, Tail Length
    
    oscThread(ofVec2f origin, ofMesh mesh);
};

#endif