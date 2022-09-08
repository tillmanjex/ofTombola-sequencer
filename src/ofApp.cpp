#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    box2d.init();
    box2d.setGravity(0, 10);
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
    tVerts.push_back(v0);
    tVerts.push_back(v1);
    tVerts.push_back(v2);
    tVerts.push_back(v3);
    tVerts.push_back(v4);
    tVerts.push_back(v5);
    tVerts.push_back(v6);
    tVerts.push_back(v7);
    tVerts.push_back(v8);
    tVerts.push_back(v9);
    tVerts.push_back(v10);
    tVerts.push_back(v11);
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    radius = 200;
    box2d.update();
    
    v0.set(canvasCenter.x + radius * cos(glm::radians(0.0)), canvasCenter.y + radius * sin(glm::radians(0.0)), 0);
    v1.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    v2.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    v3.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    v4.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    v5.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    v6.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    v7.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    v8.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    v9.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    v10.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    v11.set(canvasCenter.x + radius * cos(glm::radians(360.0)), canvasCenter.y + radius * sin(glm::radians(360.0)), 0);
    
    tombolaVerts();

}

//--------------------------------------------------------------
void ofApp::draw(){
   
    
    
    for (auto &circle : circles){
        circle->draw();
    };
    

    
    for (auto &edge : tombolaEdges){
        edge->draw();
    };
    
    tEdge0.draw();
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
    
  //  ballsVector.push_back(ball);
    // make a shared circle
    auto circle = std::make_shared<ofxBox2dCircle>();
    circle->setPhysics(1, 0.7, 0.7);
    circle->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 3);
    
    circles.push_back(circle);
    
    
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


void ofApp::tombolaVerts(){
    
    // vertex points for hexagon
    


//    tVerts.at(0).set(v0);
//    tVerts.at(1).set(v1);
//    tVerts.at(2).set(v2);
//    tVerts.at(3).set(v3);
//    tVerts.at(4).set(v4);
//    tVerts.at(5).set(v5);
//    tVerts.at(6).set(v6);
//    tVerts.at(7).set(v7);
//    tVerts.at(8).set(v8);
//    tVerts.at(9).set(v9);
//    tVerts.at(10).set(v10);
//    tVerts.at(11).set(v11);
  
//    tLine0.addVertex(tVerts[0]);
//    tLine0.addVertex(tVerts[1]);
    
    tEdge0.addVertex(v0);
    tEdge0.addVertex(v1);
    
    tEdge0.create(box2d.getWorld());

    
//    for (int i = 0; i < tVerts.size(); i++) {
//        lines.push_back(ofPolyline());
//        lines.back().addVertex(tVerts[i]);
//      //lines.back().simplify(); // double check what this actually does...
//    };
//
//    auto edge = std::make_shared<ofxBox2dEdge>();
//
//    for (int i = 0; i < lines.size(); i++) {
//        edge->addVertex(lines.back()[i]);
//    };
//    edge->create(box2d.getWorld());
//    tombolaEdges.push_back(edge);
    
}
