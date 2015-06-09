#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    //origin and destination points
    targets.addVertex(ofVec3f(-150,0));
    targets.addColor(ofColor(255));
    targets.addVertex(ofVec3f(150,50,50));
    targets.addColor(ofColor(255));
    
    targets.setMode(OF_PRIMITIVE_POINTS);
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    
    //line to be transformed
    originP = targets.getVertex(0);
    destP = targets.getVertex(1);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    tempO.set(-length/2,0);
    tempD.set(length/2,0);
    
    float time = ofGetElapsedTimef()/5;
    
    for (float x=0;x<150;x++){
        float delta = x/150;
        ofVec3f signal = tempO.getInterpolated(tempD, delta);
        
        connections.addVertex(signal);
        connections.addColor(0);
    }
    
    connections.setMode(OF_PRIMITIVE_LINE_STRIP);
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    
    speed = 60; // Same as framerate
}

//--------------------------------------------------------------
void ofApp::update(){
    int leadVertex = fmodf(ofGetElapsedTimef()*speed,150);
    
    for(int i=0; i<150; i++){
        connections.setColor(i,ofColor(ofColor(255),0));
    }
    
    for(int i=0, cc=50; i<50; i++,cc--){
        connections.setColor(leadVertex-i,ofColor(ofColor(255),ofMap(cc,0,50,0,255)));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofBackground(ofColor(0));
    
    ofDrawBitmapString("Speed = " + ofToString(speed),10,10);
    
    cam.begin();
        
        ofPushMatrix();
        
            ofTranslate((originP.x+destP.x)/2,(originP.y+destP.y)/2,(originP.z+destP.z)/2);
            
            ofVec3f direction = (destP - originP).getNormalized();
            float rotationAmount;
            ofVec3f rotationAngle;
            ofQuaternion rotation;
            ofVec3f axis(1, 0, 0);
            rotation.makeRotate(axis, direction);
            rotation.getRotate(rotationAmount, rotationAngle);
            ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
            connections.draw();
        
        ofPopMatrix();

    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        for (float x=0;x<150;x++){
            connections.setColor(x,ofColor(255));
        }
    }
    
    if(key=='-'){
        speed--;
    }
    
    if(key=='='){
        speed++;
    }
}
