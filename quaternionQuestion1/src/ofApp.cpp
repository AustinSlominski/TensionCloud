#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //origin and destination points
    targets.addVertex(ofVec3f(-150,0));
    targets.addColor(ofColor(255));
    targets.addVertex(ofVec3f(-150,100,50));
    targets.addColor(ofColor(255));
    
    targets.setMode(OF_PRIMITIVE_POINTS);
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    
    //line to be transformed
    originP = targets.getVertex(0);
    destP = targets.getVertex(1);
    
    length = sqrt(pow(destP.x-originP.x,2)+pow(destP.y-originP.y,2)+pow(destP.z-originP.z,2));
    
    //Finding the angle of rotation to match that of the origin and destination points
    angleRotX = atan2((destP.z-originP.z),(destP.y-originP.y))*180/PI;
    angleRotY = atan2((destP.z-originP.z),(destP.x-originP.x))*180/PI;
    angleRotZ = atan2((destP.y-originP.y),(destP.x-originP.x))*180/PI;
    
    roll.makeRotate(angleRotX, ofVec3f(1,0,0));
    yaw.makeRotate(angleRotY, ofVec3f(0,1,0));
    pitch.makeRotate(angleRotZ, ofVec3f(0,0,1));
    curRot = roll*pitch*yaw;
    
    tempO.set(-length/2,0);
    tempD.set(length/2,0);
    
    float time = ofGetElapsedTimef()/5;
    
    for (float x=0;x<150;x++){
        float delta = x/150;
        ofVec3f signal = tempO.getInterpolated(tempD, delta);
        
        connections.addVertex(signal);
        connections.addColor(150);
    }
    
    connections.setMode(OF_PRIMITIVE_LINE_STRIP);
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofBackground(ofColor(0));
    
    cam.begin();
        //Euler
        ofLine(-300,0,300,0);
        ofSetColor(255,0,0);
        ofLine(0,300,0,-300);
        ofSetColor(0,255,0);
        ofLine(0,0,300,0,0,-300);
        ofSetColor(0,0,255);

        targets.draw();
    
        ofPushMatrix();
            ofTranslate((originP.x+destP.x)/2,(originP.y+destP.y)/2,(originP.z+destP.z)/2);
            ofVec3f axis;
            float angle;
            curRot.getRotate(angle, axis);
            ofRotate(angle, axis.x, axis.y, axis.z);
            connections.draw();
        ofPopMatrix();
    cam.end();
    

}
