#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh.addVertex(ofVec3f(-150,0));
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(150,0));
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(200,50));
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(50,0));
    mesh.addColor(ofColor(255));
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(braid.size()>0){
        for(int i=0;i<braid.size();i++){
            for(int j=0;j<braid[i].size();j++){
                braid[i][j].update();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofBackgroundGradient(ofColor(50), ofColor(0));
    
    cam.begin();
    mesh.draw();
    if(braid.size()>0){
        for(int i=0;i<braid.size();i++){
            for(int j=0;j<braid[i].size();j++){
                braid[i][j].draw();
            }
        }
    }
    cam.end();
    
    ofDrawBitmapString("Number of Braids: " + ofToString(braid.size()),10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        vector<oscThread> tempBraid;    //Inner vector
        ofVec2f tempOrigin;             //Origin/dest vector
        tempOrigin.set(ofRandom(4),ofRandom(4));   //Number of vertices in point cloud
        
        for(int i=0;i<1;i++){
            tempBraid.push_back(oscThread(tempOrigin,mesh));
            tempBraid.back().setup();   //Setup new threads
        }
        
        braid.push_back(tempBraid);     //Finally insert tempBraid into outer vector
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
