#include "oscThread.h"

oscThread::oscThread(ofVec2f origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin.x);
    destP = mesh.getVertex(origin.y);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    //consider defining in update, to allow for point jitter!
    angleRotZ = atan2((destP.y-originP.y),(destP.x-originP.x))*180/PI;
    
    tempO.set(0,0);
    tempD.set(length,0);
    
    color = ofColor(ofRandom(200));
    res   = 200;                            //Resolution (also relates to actual freq?)
    speed = 5;                              //Speed (lower=faster)
    amp   = 10;                             //Amplitude
    f     = 3;                              //Frequency
    
    numVerts  = 0;
}

void oscThread::setup()
{
    numVerts = this->getMesh().getNumVertices();
    float time = ofGetElapsedTimef()/speed;
    
    for (float x=0;x<res;x++){
        float delta = x/res;
        float p = x;
        float oscillation = amp * sin((2 * pi * f * time + p)/20);
        
        ofVec3f signal = tempO.getInterpolated(tempD, delta);
        signal.set(signal);
        
        ofPushMatrix();
            signal.z = oscillation;
        ofPopMatrix();
        
        this->getMesh().addVertex(signal);
        this->getMesh().addColor(color);
        
        numVerts++;
    }
    
    this->getMesh().setMode(OF_PRIMITIVE_LINE_STRIP);
    
    //VBO TESTING
    this->setUseVbo(TRUE);
    
    glLineWidth(2);
}

void oscThread::draw()
{
    ofPushMatrix();
        //ofRotateX(angleRotX);
        //ofRotateY(angleRotY);
        ofRotateZ(angleRotZ);
        ofTranslate(originP.x,originP.y);
    ofLog(OF_LOG_NOTICE,"Center for Transform: " + ofToString(originP.x) + ", " + ofToString(originP.y));
        transformGL();
            this->getMesh().draw();
        restoreTransformGL();
    ofPopMatrix();

}

void oscThread::update()
{
    float time = ofGetElapsedTimef()/speed;
    
    for (int x=0;x<res;x++){
        ofVec3f oscTemp = this->getMesh().getVertex(x);
        float p = x;
        float oscillation = amp * sin(2 * pi * f * time + p)/20;

        oscTemp.rotate(x/f,ofVec3f(1,0,0));
        
        this->getMesh().setVertex(x,oscTemp);
    }
    
    this->tilt(0.01); // Constant rotation
}
