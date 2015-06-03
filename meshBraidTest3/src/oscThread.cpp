#include "oscThread.h"

oscThread::oscThread(ofVec2f origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin.x);
    destP = mesh.getVertex(origin.y);//x and y should be checked to be unique, or
    //else they can both point to the same index
    
    //! The length of the braid also plays a role in the shape of the inner circle
    
    color = ofColor(ofRandom(200));
    res   = 100;                            //Resolution (also relates to actual freq?)
    speed = 5;                              //Speed (lower=faster)
    amp   = 10;                             //Amplitude
    f     = 10;                             //Frequency
    
    helixTest = sin(f*amp);                 //Affecting the shape of the spiral!
    numVerts  = 0;
}

void oscThread::setup()
{
    float time = ofGetElapsedTimef()/speed;
    numVerts = this->getMesh().getNumVertices();
    
    this->getMesh().addVertex(originP);
    this->getMesh().addColor(color);
    
    
    for (float x=0;x<res;x++){
        float delta = x/res;
        float p = x;  //Phase
        float oscillation = amp * sin(2 * pi * f * time + p);
        ofVec3f signal = originP.getInterpolated(destP, delta);
        //offsetZ.push_back(signal.z);
        /*
         ofPushMatrix();
         signal.z = oscillation;
         signal.rotate(helixTest+x,ofVec3f(1,0,0));
         ofPopMatrix();
         */
        this->getMesh().addVertex(signal);
        this->getMesh().addColor(color);
        
        numVerts++;
    }
    
    
    this->getMesh().addVertex(destP);
    this->getMesh().addColor(color);
    
    this->getMesh().setMode(OF_PRIMITIVE_LINE_STRIP);
    
    //VBO TESTING
    this->setUseVbo(TRUE);
    
    glLineWidth(2);
}

void oscThread::draw()
{
    transformGL();
    this->getMesh().draw();
    restoreTransformGL();
}

void oscThread::update()
{
    float time = ofGetElapsedTimef()/speed;
    
    for (int x=0;x<res;x++){
        float delta = x/res;
        float p = x; //Phase
        float oscillation = amp * sin(2 * pi * f * time + p);
        ofVec3f oscTemp = this->getMesh().getVertex(x);
        //oscTemp.z = oscillation + offsetZ[x]; // I just entirely overwrite the initial z values...
        oscTemp.z = oscillation;
        ofPushMatrix();
        oscTemp.rotate(helixTest+x,ofVec3f(1,0,0));
        ofPopMatrix();
        
        //Something about the oscillation of the z axis is keeping me from actually getting the braids to draw diagonally. It's all flush with z. Add the oscillation to the original interpolation
        
        this->getMesh().setVertex(x,oscTemp);
    }
    
    //this->tilt(0.01); // Constant rotation BROKEN
}