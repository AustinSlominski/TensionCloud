#include "oscThread.h"

oscThread::oscThread(int origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin);
    destP   = mesh.getVertex(origin+1);
    
    color = ofColor(ofRandom(200));
    res   = ofRandom(200);      //Resolution (also relates to actual freq?)
    speed = ofRandom(5);        //Speed (lower=faster)
    amp   = ofRandom(10);       //Amplitude
    f     = ofRandom(10);       //Frequency
    
    helixTest = sin(f*amp);     //Affecting the shape of the spiral!
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
        
        ofPushMatrix();
            signal.z = oscillation;
            signal.rotate(helixTest+x,ofVec3f(1,0,0));
        ofPopMatrix();
        
        this->getMesh().addVertex(signal);
        this->getMesh().addColor(color);
        
        numVerts++;
    }
    
    this->getMesh().addVertex(destP);
    this->getMesh().addColor(color);
    
    this->getMesh().setupIndicesAuto();
    this->getMesh().setMode(OF_PRIMITIVE_LINE_STRIP);
    
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
        
        ofPushMatrix();
            oscTemp.z = oscillation;
            oscTemp.rotate(helixTest+x,ofVec3f(1,0,0));
        ofPopMatrix();
        
        this->getMesh().setVertex(x,oscTemp);
    }
    
    //this->tilt(0.01); // Constant rotation
}
