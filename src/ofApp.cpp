#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    // Utility
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2); // (512, 384)
    
    // datGui
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT);
    ofxDatGuiButton* ballSpawn = gui->addButton("Spawn Ball");
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    
    ofxDatGuiSlider* sliderRadius = gui->addSlider("Tombola Size", -1.0, 1.0);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    // ofxBox2d fps/gravity x,y)
    box2d.init(60.0, 0, 10);
    
    // Custom Functions
    tombolaInit();
    
    
    
}
//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    
    if (e.target->is("Spawn Ball")) {
        // make a shared circle
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(1, 0.7, 0.7);
        circle->setup(box2d.getWorld(), canvasCenter.x, canvasCenter.y, 5);
        circle->shouldRemoveOffScreen(circle);
        circles.push_back(circle);
    }

}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    
    for (auto &edge : tEdges){
        if (e.target->is("Tombola Size")) {
//            v0.set(e.value * cos(glm::radians(0.0)), e.value * sin(glm::radians(0.0)), 0);
//            v1.set(e.value * cos(glm::radians(60.0)), e.value * sin(glm::radians(60.0)), 0);
//            v2.set(e.value * cos(glm::radians(120.0)), e.value * sin(glm::radians(120.0)), 0);
//            v3.set(e.value * cos(glm::radians(180.0)), e.value * sin(glm::radians(180.0)), 0);
//            v4.set(e.value * cos(glm::radians(240.0)), e.value * sin(glm::radians(240.0)), 0);
//            v5.set(e.value * cos(glm::radians(300.0)), e.value * sin(glm::radians(300.0)), 0);
//
//            tLine0.clear();
//            tLine0.addVertex(v0);
//            tLine0.addVertex(v1);
//
//            tLine1.clear();
//            tLine1.addVertex(v1);
//            tLine1.addVertex(v2);
//
//            tLine2.clear();
//            tLine2.addVertex(v2);
//            tLine2.addVertex(v3);
//
//            tLine3.clear();
//            tLine3.addVertex(v3);
//            tLine3.addVertex(v4);
//
//            tLine4.clear();
//            tLine4.addVertex(v4);
//            tLine4.addVertex(v5);
//
//            tLine5.clear();
//            tLine5.addVertex(v5);
//            tLine5.addVertex(v0);

            edge->scale(e.value, e.value);
            edge->create(box2d.getWorld());
            cout << e.value << endl;
        };
        
    };
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    box2d.update();
    gui->update();

    
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    gui->draw();

    
    for (auto &circle : circles){
        ofFill();
        ofSetColor(255);
        circle->draw();
    };
    

    for (auto &edge : tEdges){
        ofSetColor(255, 0, 80);
        
        ofTranslate(canvasCenter.x, canvasCenter.y);
        edge->setPosition(canvasCenter);
        edge->draw();
       
    };

    

};
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        // use it for testing
        
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


void ofApp::tombolaInit(){

    // vertex positions for tomobola
    v0.set(200, 0, 0);
    v1.set(100, 173, 0);
    v2.set(-100, 173, 0);
    v3.set(-200, 0, 0);
    v4.set(-100, -173, 0);
    v5.set(100, -173, 0);
    
    // Creating polylines for use in ofxBoxEdges
    // Could probably also do this in a vector, but got confused by how a vector of polylines works
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
    
    
}
