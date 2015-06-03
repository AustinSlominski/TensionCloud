#include "oscThread.h"

oscThread::oscThread(ofVec2f origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin.x);
    destP = mesh.getVertex(origin.y);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    //consider defining in update, to allow for point jitter!
    //someone has suggested this to be more efficient
    //sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    //IT IS X THAT ISN'T WORKING PROPERLYfff
    angleRotX = atan2((destP.y-originP.y),(destP.z-originP.z))*180/PI;
    angleRotY = atan2((destP.z-originP.z),(destP.x-originP.x))*180/PI;
    angleRotZ = atan2((destP.y-originP.y),(destP.x-originP.x))*180/PI;
    
    ofLog(OF_LOG_NOTICE,"Angle of Rotation: X: " + ofToString(angleRotX) + " Y: " + ofToString(angleRotY) + " Z: " + ofToString(angleRotZ));
    
    roll.makeRotate(angleRotX, ofVec3f(1,0,0));
    yaw.makeRotate(angleRotY, ofVec3f(0,1,0));
    pitch.makeRotate(angleRotZ, ofVec3f(0,0,1));
    curRot = roll*pitch*yaw;
    
    tempO.set(-length/2,0);
    tempD.set(length/2,0);
    
    //Rethink these variables, and in what context do they REALLY have influence?
    color = ofColor(ofRandom(255));
    res   = 200;
    speed = 5;
    amp   = 10;
    f     = 3;
    
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
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
}

void oscThread::draw()
{
    ofPushMatrix();
        ofTranslate((originP.x+destP.x)/2,(originP.y+destP.y)/2,(originP.z+destP.z)/2);
        ofVec3f axis;
        float angle;
        curRot.getRotate(angle, axis);
        ofRotate(angle, axis.x, axis.y, axis.z);
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
}
