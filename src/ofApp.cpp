#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // Utility
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2); // (512, 384)
    
    // ofxMidi
    midi.openPort(0);
    outPorts = midi.getOutPortList();
    
    
    // ofxDatGui
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT);
    
    ofxDatGuiButton* ballSpawn = gui->addButton("Spawn Ball");
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    
    ofxDatGuiSlider* sliderRadius = gui->addSlider("Tombola Size", 100, 300);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiSlider* sliderRotate = gui->addSlider("Tombola Rotate", -5, 5);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiLabel* midiOut = gui->addLabel("Midi Out Select (Below)");

    // make as many buttons to open ports as there are ports available.
    // datGui dropdown box had impossible bugs for me to fix.
    // This was the only good alternate option.
    for (int i = 0; i < outPorts.size(); i++) {
        // outPorts.push_back(midiOut.getOutPortList()[i]);
        gui->addButton(outPorts[i]);
        gui->onButtonEvent(this, &ofApp::onButtonEvent);
    };
    
    // ofxBox2d fps/gravity x,y)
    box2d.init(60.0, 0, 10);
    box2d.enableEvents();
//    box2d.enableGrabbing() // maybe implement this later
    
    // register the contact listeners
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
    
    // Custom Functions
    tombolaInit();
    
    
    
    
}
//--------------------------------------------------------------
void ofApp::exit() {
    
    // clean up
    midi.closePort();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    box2d.update();
    gui->update();
    midiVoice.update(midi.getName(), 1, 0);

    
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
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    
    if (e.target->is("Spawn Ball")) {
        // make a shared circle
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(1, 0.7, 0.7);
        circle->setup(box2d.getWorld(), canvasCenter.x, canvasCenter.y, 5);
        circle->shouldRemoveOffScreen(circle);
        circles.push_back(circle);
    };
    
    // check against all port options if they were clicked
    // if so, then close other ports and open the clicked port
    for (int i=0; i < outPorts.size(); i++) {
        if (e.target->is(outPorts[i])) {
            // close other ports first
//            midi.closePort();
            midi.openPort(outPorts[i]);
            cout << "port" << outPorts[i] << "opened" << endl;
        };
    };

    
    

}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    
    // clear polylines for fresh input
    tLine0.clear();
    tLine1.clear();
    tLine2.clear();
    tLine3.clear();
    tLine4.clear();
    tLine5.clear();
    
    for (auto &edge : tEdges){
        // clear &edge on each iteration for correct drawing behavior
        edge->clear();
        
        if (e.target->is("Tombola Size")){

            v0.set(e.value * cos(glm::radians(0.0)), e.value * sin(glm::radians(0.0)), 0);
            v1.set(e.value * cos(glm::radians(60.0)), e.value * sin(glm::radians(60.0)), 0);
            v2.set(e.value * cos(glm::radians(120.0)), e.value * sin(glm::radians(120.0)), 0);
            v3.set(e.value * cos(glm::radians(180.0)), e.value * sin(glm::radians(180.0)), 0);
            v4.set(e.value * cos(glm::radians(240.0)), e.value * sin(glm::radians(240.0)), 0);
            v5.set(e.value * cos(glm::radians(300.0)), e.value * sin(glm::radians(300.0)), 0);
            
        } else if (e.target->is("Tombola Rotate")) {
            
            v0.rotate(e.value, ofVec3f(0, 0, 1));
            v1.rotate(e.value, ofVec3f(0, 0, 1));
            v2.rotate(e.value, ofVec3f(0, 0, 1));
            v3.rotate(e.value, ofVec3f(0, 0, 1));
            v4.rotate(e.value, ofVec3f(0, 0, 1));
            v5.rotate(e.value, ofVec3f(0, 0, 1));
        }
            // add the updated verticies to the polyline objects
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
               
            // add the updated polylines to edges
            edge->addVertexes(tLine0);
            edge->addVertexes(tLine1);
            edge->addVertexes(tLine2);
            edge->addVertexes(tLine3);
            edge->addVertexes(tLine4);
            edge->addVertexes(tLine5);
            edge->create(box2d.getWorld());
            
    };
    
    
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        if(e.a->GetType() == b2Shape::e_edge || e.b->GetType() == b2Shape::e_edge) {
            cout << "contact start" << endl;
//            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
//            if(aData) {
//                aData->bHit = true;
//                sound[aData->soundID].play();
//            }
//
//            if(bData) {
//                bData->bHit = true;
//                sound[bData->soundID].play();
//            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        cout << "contact end" << endl;
//        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//
//        if(aData) {
//            aData->bHit = false;
//        }
//
//        if(bData) {
//            bData->bHit = false;
//        }
    }
}

//--------------------------------------------------------------
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
    // (using the ofVec3s here instead of calculating inside incase I need easy access to them as variables...)
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


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        // use it for testing
        midiVoice.playNote();

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



