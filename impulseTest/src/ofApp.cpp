#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(TRUE);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    numVerts = 20;
    
    for(int i=0;i<numVerts;i++){
        mesh.addVertex(ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(600)));
        mesh.addColor(ofColor(ofRandom(255)));
        
        offsets.push_back(ofVec3f(ofRandom(0,10000),ofRandom(0,10000),ofRandom(0,10000)));
        
        mesh.setupIndicesAuto();
    }
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);
}

//--------------------------------------------------------------
void ofApp::update(){
    numVerts = mesh.getNumVertices();
    
    //Point Jitter
    for(int i=0;i<numVerts; i++){
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    cam.begin();
        ofPushMatrix();
            ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
            ofBackground(0,0,0);
            mesh.draw();
        ofPopMatrix();
    cam.end();
    
    //DEBUGGING
    ofDrawBitmapString("Number of Vertices: "+ofToString(numVerts),10,20);
    ofDrawBitmapString("Number of Indices: "+ofToString(mesh.getNumIndices()),10,40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='o'){
        //Fisher-Yates Shuffle
        for (int i = numVerts - 1; i >= 0; i --) {
            int index = (int)ofRandom(i);
            int tempIndex = mesh.getIndex(index);
            mesh.setIndex(index, mesh.getIndex(i));
            mesh.setIndex(i, tempIndex);
        }
    }
    
    if(key == 'p'){
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    if(key == 'l'){
        mesh.setMode(OF_PRIMITIVE_LINES);
    }
    
    if(key=='-'){
        if(numVerts>0){
            mesh.removeVertex(numVerts-1);
            offsets.resize(numVerts-1);
            
            mesh.setupIndicesAuto();
        }
    }
    
    if(key=='='){
        mesh.addVertex(ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(600)));
        mesh.addColor(ofFloatColor(255,255,255));
        
        offsets.push_back(ofVec3f(ofRandom(0,10000),ofRandom(0,10000),ofRandom(0,10000)));
        
        mesh.setupIndicesAuto();
    }
    
    if(key=='f'){
        int tempFire = ofRandom(numVerts);//Select random vertex
        int tempDest = NULL;
        
        if(tempFire%2){ //if number is odd
            tempFire --;//make the origin point even...
        }
        
        tempDest = mesh.getIndex(tempFire+1);
        ofVec3f firingNeuron = mesh.getVertex(tempFire);
        ofVec3f destNeuron = mesh.getVertex(tempDest);
        
        //DRAW along the path between two points
        
        vector<ofThread> tempThread;
        
    }
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
