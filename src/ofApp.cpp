#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(60.0);
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    tombolaVerts();
    
//    tVerts.push_back(v0);
//    tVerts.push_back(v1);
//    tVerts.push_back(v2);
//    tVerts.push_back(v3);
//    tVerts.push_back(v4);
//    tVerts.push_back(v5);
//    tVerts.push_back(v6);
//    tVerts.push_back(v7);
//    tVerts.push_back(v8);
//    tVerts.push_back(v9);
//    tVerts.push_back(v10);
//    tVerts.push_back(v11);
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    box2d.update();

    
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    
    
    for (auto &circle : circles){
        ofFill();
        ofSetColor(255);
        circle->draw();
    };
    

    
    for (auto &edge : tEdges){
        ofSetColor(255, 0, 80);
        edge->draw();
        
    };
    

};
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        // use it for testing

        
        radius = .5;
      
//        tLine0.scale(.1, .1);
//        tLine1.scale(.1, .1);
//        tLine2.scale(.1, .1);
//        tLine3.scale(.1, .1);
//        tLine4.scale(.1, .1);
//        tLine5.scale(.1, .1);
        
        for (auto &edge : tEdges){
            // edge->clear();
            
            
            ofPushMatrix();
            
            //edge->setRotation(20);
            
            edge->scale(radius, radius);
            edge->create(box2d.getWorld());
            ofPopMatrix();

        };

        
        cout << "key pressed: a" << endl;
    };
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
    circle->setup(box2d.getWorld(), mouseX, mouseY, 5);
    circle->shouldRemoveOffScreen(circle);
    
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

    // vertex positions for tomobola
    v0.set(712, 384, 0);
    v1.set(612, 557.205, 0);
    v2.set(412, 557.205, 0);
    v3.set(312, 384, 0);
    v4.set(412, 210.795, 0);
    v5.set(612, 210.795, 0);
    
    // Creating polylines for use in ofxBoxEdges
    tLine0.addVertex(v0);
    tLine0.addVertex(v1);
    
    tLine1.addVertex(v1);
    tLine1.addVertex(v2);
    
    tLine2.addVertex(v2);
    tLine2.addVertex(v3);
    
    tLine3.addVertex(v3);
    tLine3.addVertex(v4);
    
    tLine4.addVertex(v4);
    tLine4.addVertex(v5);
    
    tLine5.addVertex(v5);
    tLine5.addVertex(v0);

    // Creating edges
    auto edge = std::make_shared<ofxBox2dEdge>();
    edge->addVertexes(tLine0);
    edge->addVertexes(tLine1);
    edge->addVertexes(tLine2);
    edge->addVertexes(tLine3);
    edge->addVertexes(tLine4);
    edge->addVertexes(tLine5);
    edge->create(box2d.getWorld());
    tEdges.push_back(edge);
    

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
  

//    v0.set(712, 384, 0);
//    v1.set(612, 557.205, 0);
//    v2.set(612, 557.205, 0);
//    v3.set(412, 557.205, 0);
//    v4.set(412, 557.205, 0);
//    v5.set(312, 384, 0);
//    v6.set(312, 384, 0);
//    v7.set(412, 210.795, 0);
//    v8.set(412, 210.795, 0);
//    v9.set(612, 210.795, 0);
//    v10.set(612, 210.795, 0);
//    v11.set(712, 384, 0);
        
//    tEdge0.addVertexes(tLine0);
//    tEdge0.create(box2d.getWorld());
//
//    tEdge1.addVertexes(tLine1);
//    tEdge1.create(box2d.getWorld());
//
//    tEdge2.addVertexes(tLine2);
//    tEdge2.create(box2d.getWorld());
//
//    tEdge3.addVertexes(tLine3);
//    tEdge3.create(box2d.getWorld());
//
//    tEdge4.addVertexes(tLine4);
//    tEdge4.create(box2d.getWorld());
//
//    tEdge5.addVertexes(tLine5);
//    tEdge5.create(box2d.getWorld());
//




    
}
