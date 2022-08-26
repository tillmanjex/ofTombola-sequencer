#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < ballsVector.size(); i++){
        ballsVector[i].update();
        if (ballsVector[i].location.y > ofGetHeight()) {
            ballsVector.erase(ballsVector.begin()+i);
            
        };
    };
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    tombola.draw();
    for (int i = 0; i < ballsVector.size(); i++){
        ballsVector[i].draw();
    };

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        // use it for testin
        cout << "key pressed: a" << endl;
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
    
    ballsVector.push_back(ball);
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
