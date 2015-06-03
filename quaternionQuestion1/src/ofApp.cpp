#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    length = 111.803398;

    //Finding the angle of rotation to match that of the origin and destination points
    angleRotX = atan2((100-0),(50-0))*180/PI;
    angleRotY = atan2((50-0),(-150+150))*180/PI;
    angleRotZ = atan2((100-0),(-150+150))*180/PI;
    
    roll.makeRotate(angleRotX, ofVec3f(1,0,0));
    yaw.makeRotate(angleRotY, ofVec3f(0,1,0));
    pitch.makeRotate(angleRotZ, ofVec3f(0,0,1));
    curRot = roll*pitch*yaw;
    
    
    tempO.set(-55.9,0);
    tempD.set(55.9);
    
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
    
    //origin and destination points
    mesh.addVertex(ofVec3f(-150,0));
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(-150,100,50));
    mesh.addColor(ofColor(255));
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
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

        mesh.draw();
    
        ofPushMatrix();
            ofTranslate((-150-150)/2,(0+100)/2,(0+50)/2);
            ofVec3f axis;
            float angle;
            curRot.getRotate(angle, axis);
            ofRotate(angle, axis.x, axis.y, axis.z);
            connections.draw();
        ofPopMatrix();
    cam.end();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
