#include "oscThread.h"

oscThread::oscThread(ofVec2f origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin.x);
    destP = mesh.getVertex(origin.y);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    tempO.set(-length/2,0);
    tempD.set(length/2,0);
    
    //Rethink these variables, and in what context do they REALLY have influence?
    color = ofColor(ofRandom(255));
    res   = 150;
    speed = 5;
    cSpeed = 80; //RENAME
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
        direction = (destP - originP).getNormalized();
        axis.set(1, 0, 0);
        rotation.makeRotate(axis, direction);
        rotation.getRotate(rotationAmount, rotationAngle);
        ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
        transformGL();
            this->getMesh().draw();
        restoreTransformGL();
    ofPopMatrix();
}

void oscThread::update()
{
    float time = ofGetElapsedTimef()/speed;
    int leadVertex = fmodf(ofGetElapsedTimef()*cSpeed,res);
    
    for (int x=0;x<res;x++){
        ofVec3f oscTemp = this->getMesh().getVertex(x);
        float p = x;
        float oscillation = amp * sin(2 * pi * f * time + p)/20;
        oscTemp.rotate(x/f,ofVec3f(1,0,0));
        this->getMesh().setVertex(x,oscTemp);
        this->getMesh().setColor(x,ofColor(ofColor(255),0));
    }

    for(int i=0, cc=50; i<50; i++,cc--){//50 is trail length
        this->getMesh().setColor(leadVertex-i,ofColor(ofColor(255),ofMap(cc,0,50,0,255)));
    }
}
