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
    
    gui->addBreak();
    
//    ofxDatGuiButton* getPorts = gui->addButton("Get Midi Out Ports");
//    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    
    // make as many buttons to open ports as there are ports available.
    // datGui dropdown box had impossible bugs for me to fix.
    // This was the only good alternate option.
    for (int i = 0; i < outPorts.size(); i++) {
        // outPorts.push_back(midiOut.getOutPortList()[i]);
        gui->addButton("out: " + outPorts[i]);
        gui->onButtonEvent(this, &ofApp::onButtonEvent);
    };
    
    // ofxBox2d fps/gravity x,y)
    box2d.init(60.0, 0, 10);
    box2d.enableEvents();
    box2d.createBounds(ofRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight()));
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
    midiVoice.update(midi.getName(), 1, 0);
    
    
    for (auto &rect : tRects){
        rect->setPhysics(3.0, 0.5, 1.0);
        rect->getWorld();
    }
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    gui->draw();

    
    for (auto &circle : circles){
        ofFill();
        ofSetColor(255);
        circle->draw();
    };
    

//    for (auto &edge : tEdges){
//        ofSetColor(255, 0, 80);
//        ofPushMatrix();
//        ofTranslate(canvasCenter.x, canvasCenter.y);
//        edge->setPosition(canvasCenter);
//        edge->draw();
//        ofPopMatrix();
//    };
    
    
    for (auto &rect : tRects){
        ofSetColor(0, 255, 80);
        ofPushMatrix();
        rect->draw();
        ofPopMatrix();
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
        
        // assign an instance of the MidiData class to the ball.
        
        circle->setData(new MidiData());
        auto * md = (MidiData*)circle->getData();
        md->bHit = false;
        
        circles.push_back(circle);
    };
    
    // come back to this. I want to update the current buttons,
//    if (e.target->is("Get Midi Out Ports")){
//        for (int i = 0; i < outPorts.size(); i++) {
//            if (gui->getButton(outPorts[i])->getLabel() == outPorts[i]){
//                cout << "do nothing" << endl;
//            } else
//            if (gui->getButton(outPorts[i])->getLabel() != outPorts[i]){
//                cout << "should add" << endl;
//            gui->addButton(outPorts[i]);
//            gui->onButtonEvent(this, &ofApp::onButtonEvent);
//        };
//    };
    
    // check against all port options if they were clicked
    // if so, then close other ports and open the clicked port
    for (int i=0; i < outPorts.size(); i++) {
        if (e.target->is(outPorts[i])) {
            // close other ports first
            midi.closePort();
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
        
        // Check what objects are colliding (it seems like a nonsensical
        // check, but without it I was getting pointer access errors...
//        if(e.a->GetType() == b2Shape::e_circle || e.a->GetType() == b2Shape::e_polygon) {
            
            cout << "contact start" << endl;
            
            // Dont fully understand what's happening here,
            // but it seems like aData is being set as a pointer to MidiData
            // and - as it now takes the class form - can subsequently use
            // methods from that class as well as the contact listner class
            MidiData * aData = (MidiData*)e.a->GetBody()->GetUserData();
            MidiData * bData = (MidiData*)e.b->GetBody()->GetUserData();


            if(aData) {
//                aData->bHit = true;
                bData->update(midi.getName(), 1, 0);
                bData->playNote();
                cout << "aData" << endl;
            };

            if(bData) {
//                bData->bHit = true;
                bData->update(midi.getName(), 1, 0);
                bData->playNote();
                cout << "bData" << endl;
//            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {

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
    
    // derive the central point between each pair of vectors above
    // [v0 and v1], [v1 and v2] etc
    v0r.set(canvasCenter.x + v0.x - (v1.x / 2), canvasCenter.y + v0.y - (v1.y / 2));
    v1r.set(canvasCenter.x + v1.x - (v2.x / 2), canvasCenter.y + v1.y - (v2.y / 2));
    v2r.set(canvasCenter.x + v2.x - (v3.x / 2), canvasCenter.y + v2.y - (v3.y / 2));
    v3r.set(canvasCenter.x + v3.x - (v4.x / 2), canvasCenter.y + v3.y - (v4.y / 2));
    v4r.set(canvasCenter.x + v4.x - (v5.x / 2), canvasCenter.y + v4.y - (v5.y / 2));
    v5r.set(canvasCenter.x + v5.x - (v0.x / 2), canvasCenter.y + v5.y - (v0.y / 2));
    
    
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

    // this feels stupid, not sure if it's the best way.
    // But as each rect needs a differnt initial position and rotation value
    // I'm not sure how else to go about it.
    auto rect0 = std::make_shared<ofxBox2dRect>();
    auto rect1 = std::make_shared<ofxBox2dRect>();
    auto rect2 = std::make_shared<ofxBox2dRect>();
    auto rect3 = std::make_shared<ofxBox2dRect>();
    auto rect4 = std::make_shared<ofxBox2dRect>();
    auto rect5 = std::make_shared<ofxBox2dRect>();
    
    
    rect0->setup(box2d.getWorld(), v0r.x, v0r.y, 200, 2, 60);
    rect1->setup(box2d.getWorld(), v1r.x, v1r.y, 200, 2, 120);
    rect2->setup(box2d.getWorld(), v2r.x, v2r.y, 200, 2, 0);
    rect3->setup(box2d.getWorld(), v3r.x, v3r.y, 200, 2, -120);
    rect4->setup(box2d.getWorld(), v4r.x, v4r.y, 200, 2, -60);
    rect5->setup(box2d.getWorld(), v5r.x, v5r.y, 200, 2, 0);

    
    tRects.push_back(rect1);
    tRects.push_back(rect0);
    tRects.push_back(rect2);
    tRects.push_back(rect3);
    tRects.push_back(rect4);
    tRects.push_back(rect5);

    
    // Creating edges from polylines
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

    // make a shared circle
    auto circle = std::make_shared<ofxBox2dCircle>();
    circle->setPhysics(1, 0.7, 0.7);
    circle->setup(box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), 5);
    circle->shouldRemoveOffScreen(circle);
    
    // assign an instance of the MidiData class to the ball.
    
    circle->setData(new MidiData());
    auto * md = (MidiData*)circle->getData();
    md->bHit = false;
    
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
    canvasCenter.set(w / 2, h / 2);
    
    tombolaVertRecalc();

}

//--------------------------------------------------------------
void ofApp::tombolaVertRecalc(){
    
    // again. finding this pretty gross, but I couldn't find any other method that worked.
    // Setting the vectors here, and then calling .setPosition(v0r) in update
    // also did not work, and I really dont know why. But time to move on...
    tRects.clear();
    
    v0r.set(canvasCenter.x + v0.x - (v1.x / 2), canvasCenter.y + v0.y - (v1.y / 2));
    v1r.set(canvasCenter.x + v1.x - (v2.x / 2), canvasCenter.y + v1.y - (v2.y / 2));
    v2r.set(canvasCenter.x + v2.x - (v3.x / 2), canvasCenter.y + v2.y - (v3.y / 2));
    v3r.set(canvasCenter.x + v3.x - (v4.x / 2), canvasCenter.y + v3.y - (v4.y / 2));
    v4r.set(canvasCenter.x + v4.x - (v5.x / 2), canvasCenter.y + v4.y - (v5.y / 2));
    v5r.set(canvasCenter.x + v5.x - (v0.x / 2), canvasCenter.y + v5.y - (v0.y / 2));
    
    auto rect0 = std::make_shared<ofxBox2dRect>();
    auto rect1 = std::make_shared<ofxBox2dRect>();
    auto rect2 = std::make_shared<ofxBox2dRect>();
    auto rect3 = std::make_shared<ofxBox2dRect>();
    auto rect4 = std::make_shared<ofxBox2dRect>();
    auto rect5 = std::make_shared<ofxBox2dRect>();


    rect0->setup(box2d.getWorld(), v0r.x, v0r.y, 200, 2, 60);
    rect1->setup(box2d.getWorld(), v1r.x, v1r.y, 200, 2, 120);
    rect2->setup(box2d.getWorld(), v2r.x, v2r.y, 200, 2, 0);
    rect3->setup(box2d.getWorld(), v3r.x, v3r.y, 200, 2, -120);
    rect4->setup(box2d.getWorld(), v4r.x, v4r.y, 200, 2, -60);
    rect5->setup(box2d.getWorld(), v5r.x, v5r.y, 200, 2, 0);


    tRects.push_back(rect1);
    tRects.push_back(rect0);
    tRects.push_back(rect2);
    tRects.push_back(rect3);
    tRects.push_back(rect4);
    tRects.push_back(rect5);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



