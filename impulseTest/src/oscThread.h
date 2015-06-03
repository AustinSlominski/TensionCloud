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
    
        ofColor color;
    
        int   res;    //Resolution
        int   speed;  //Speed (lower=faster)
        float amp;    //Amplitude
        float f;      //Frequency
        float rot;    //Rotation
    
        int numVerts;
        float helixTest;
    
        oscThread(int origin, ofMesh mesh);
};

#endif