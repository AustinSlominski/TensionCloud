#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh.addVertex(ofVec3f(-150,0));
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(150,0));
    mesh.addColor(ofColor(255));
    
    mesh.addIndex(0);
    mesh.addIndex(1);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(oscNum>0){
        for(int i=0;i<oscNum;i++){
            updateWave(i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofBackgroundGradient(ofColor(50),ofColor(0));
    
    cam.begin();
    mesh.draw();
    for(int i=0;i<oscNum;i++){
        oscMesh[i].draw();
    }
    cam.end();
    
    ofDrawBitmapString("OSCNUM: " + ofToString(oscNum),10,10);
    ofDrawBitmapString("F: " + ofToString(f),10,20);
    ofDrawBitmapString("AMP: " + ofToString(amp),10,30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='p'){ //POINTS
        for(int i=0;i<oscNum;i++){
            oscMesh[i].getMesh().setMode(OF_PRIMITIVE_POINTS);
        }
    }
    if(key=='l'){ //LINES
        for(int i=0;i<oscNum;i++){
            oscMesh[i].getMesh().setMode(OF_PRIMITIVE_LINE_STRIP);
        }
    }
    if(key=='f'){ //FIRE
        sendWave(0,1);
    }

}

//--------------------------------------------------------------
void ofApp::sendWave(int index, int burst){
    
    ofVec3f firingPoint = mesh.getVertex(index);
    ofVec3f destPoint = mesh.getVertex(index+1);
    
    int res = 150;
    
    for(int i=0;i<burst;i++){
        oscNum++;
        oscMesh.resize(oscNum);
        
        for (float x=0;x<res;x++){
            float delta = x/res;
            
            ofVec3f signal = firingPoint.getInterpolated(destPoint, delta);
            
            oscMesh[i].getMesh().addVertex(signal);
            oscMesh[i].getMesh().addColor(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
        }
        
        oscMesh[i].getMesh().addVertex(destPoint);
        oscMesh[i].getMesh().addColor(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
        
        oscMesh[i].getMesh().setupIndicesAuto();
        oscMesh[i].getMesh().setMode(OF_PRIMITIVE_LINE_STRIP);
        
        //oscMesh[i].setPosition(firingPoint.x,firingPoint.y,firingPoint.z);
        float degree = 90;
        oscMesh[i].tilt(degree);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::updateWave(int i){
    
    speed = 5;

    float time = ofGetElapsedTimef()/speed;
    
    int res = oscMesh[i].getMesh().getNumVertices(); //Resolution
    
    for (int x=1;x<res;x++){
        float delta = x/res;
        
        float amp = 10;       //Amplitude
        float f   = 10;       //Frequency
        float p   = x;          //Phase
        
        float oscillation = amp * sin(2 * pi * f * time + p);
        ofVec3f oscTemp = oscMesh[i].getMesh().getVertex(x);
        oscTemp.z = oscillation;
        
        oscMesh[i].getMesh().setVertex(x,oscTemp);
    }
    
}