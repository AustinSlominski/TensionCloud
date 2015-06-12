#include "oscThread.h"

oscThread::oscThread(ofVec2f origin, ofMesh mesh)
{
    originP = mesh.getVertex(origin.x);
    destP = mesh.getVertex(origin.y);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    tempO.set(-length/2,0);
    tempD.set(length/2,0);
    
    //Rethink these variables, and in what context do they REALLY have influence?
    color    = ofRandom(255);   //Real color of braid. Fixed
    res      = 300;             //Resolution of line
    speed    = 5;               //??
    amp      = 10;              //??
    f        = 3;               //??
    
    numVerts = 0;
    tLength  = 100;
    cSpeed   = 40;
}

void oscThread::setup()
{
    numVerts = this->getMesh().getNumVertices();
    time = ofGetElapsedTimef();
    mTime = time/speed;
    
    for (float x=0;x<res;x++){
        float delta = x/res;
        float p = x;
        float oscillation = amp * sin((2 * pi * f * mTime + p)/20);
        
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
    time = ofGetElapsedTimef();
    mTime = time/speed;
    float dt = ofClamp(time-time0, 0, 0.1);
    
    time0 = time;
    lead += cSpeed * dt;
    
    if (lead > leadVertex){
        leadVertex = lead;
    }
    
    if (leadVertex > res){
        leadVertex = 0;
        lead = 0;
    }
    
    for (int x=0;x<res;x++){
        ofVec3f oscTemp = this->getMesh().getVertex(x);
        float p = x;
        float oscillation = amp * sin(2 * pi * f * mTime + p)/20;
        oscTemp.rotate(x/f,ofVec3f(1,0,0));
        this->getMesh().setVertex(x,oscTemp);
        this->getMesh().setColor(x,ofColor(ofColor(255),0));
    }

    if(leadVertex < tLength){
        ttLength = leadVertex;
    }else{
        ttLength = tLength;
    }
    
    for(int i=0, tC=ttLength; i<ttLength; i++,tC--){
        this->getMesh().setColor(leadVertex-i,ofColor(color,color+i,color-i,ofMap(tC,0,50,0,255)));
    }
}
