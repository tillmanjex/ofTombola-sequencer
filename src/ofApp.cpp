#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    box2d.init();
    box2d.setGravity(0, 30);
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < ballsVector.size(); i++){
        ballsVector[i].update();
        ballsVector[i].collision(tombola.tombolaVerts[0], tombola.tombolaVerts[1]);
        ballsVector[i].collision(tombola.tombolaVerts[2], tombola.tombolaVerts[3]);
        ballsVector[i].collision(tombola.tombolaVerts[4], tombola.tombolaVerts[5]);
        ballsVector[i].collision(tombola.tombolaVerts[6], tombola.tombolaVerts[7]);
        ballsVector[i].collision(tombola.tombolaVerts[8], tombola.tombolaVerts[9]);
        ballsVector[i].collision(tombola.tombolaVerts[10], tombola.tombolaVerts[11]);
        
       // cout << tombola.tombolaVerts[0] << endl;
        // remove balls from array when off screen: #works
        if (ballsVector[i].location.y > ofGetHeight()) {
            ballsVector.erase(ballsVector.begin()+i);
            
        };
    };
    
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    tombola.draw();
    for (auto & b : ballsVector){
        b.draw();
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
