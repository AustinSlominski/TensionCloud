#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    numMesh = 20;
    
    
     for(int i=0;i<numMesh;i++){
     mesh.addVertex(ofVec3f(ofRandom(-800,800),ofRandom(-800,800),ofRandom(-800,800)));
     mesh.addColor(255);
     
     offsets.push_back(ofVec3f(ofRandom(-10000,10000),ofRandom(-10000,10000),ofRandom(-10000,10000)));
     mesh.setupIndicesAuto();
     }
     
    /*
    mesh.addVertex(ofVec3f(-150,0));        //0
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(150,0));         //1
    mesh.addColor(ofColor(255));
    mesh.addVertex(ofVec3f(-150,100,50));   //2
    mesh.addColor(ofColor(255));
    */
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    //GUI
    
    gui.setup();
    gui.add(res.set("Number of Vertices",200,10,200));
    gui.add(amp.set("Amplitude",10,1,100));
    gui.add(f.set("Frequency",10,1,100));
    gui.add(speed.set("Speed",5,1,50));
    
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(braid.size()>0){
        for(int i=0;i<braid.size();i++){
            for(int j=0;j<braid[i].size();j++){
                braid[i][j].amp = amp;
                braid[i][j].speed = speed;
                braid[i][j].f = f;
                braid[i][j].update();
            }
        }
    }
    
    //Point Jitter
    /*
     for(int i=0;i<numMesh; i++){
     ofVec3f vert = mesh.getVertex(i);
     
     float time = ofGetElapsedTimef();
     float timeScale = 5.0;
     float displacementScale = 0.75;
     ofVec3f timeOffsets = offsets[i];
     
     vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
     vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
     vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
     
     mesh.setVertex(i,vert);
     }
     */
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    //ofBackgroundGradient(ofColor(50), ofColor(0));
    ofBackground(ofColor(0));
    
    cam.begin();
    
    //Euler
    /*
    ofLine(-300,0,300,0);
    ofSetColor(255,0,0);
    ofLine(0,300,0,-300);
    ofSetColor(0,255,0);
    ofLine(0,0,300,0,0,-300);
    ofSetColor(0,0,255);
    */
    
    mesh.draw();
    if(braid.size()>0){
        for(int i=0;i<braid.size();i++){
            for(int j=0;j<braid[i].size();j++){
                braid[i][j].draw();
            }
        }
    }
    cam.end();
    
    //ofDrawBitmapString("Number of Braids: " + ofToString(braid.size()),10,10);
    //gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        vector<oscThread> tempBraid;    //Inner vector
        ofVec2f tempOrigin;             //Origin/dest vector
        tempOrigin.set((int)ofRandom(numMesh),(int)ofRandom(numMesh));
        //tempOrigin.set(0,2);
        while (tempOrigin.x == tempOrigin.y){
            tempOrigin.set((int)ofRandom(numMesh),(int)ofRandom(numMesh));
        }
        
        ofLog(OF_LOG_NOTICE,"TEMPORIGIN: " + ofToString(tempOrigin.x) + ", " + ofToString(tempOrigin.y));
        
        for(int i=0;i<1;i++){ // 1 being the size of "burst"
            tempBraid.push_back(oscThread(tempOrigin,mesh));
            tempBraid.back().res = res;
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
