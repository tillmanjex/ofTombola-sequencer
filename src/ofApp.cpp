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
    
    ofxDatGuiSlider* ballMass = gui->addSlider("Ball Mass", 1.0, 100);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiSlider* ballBounce = gui->addSlider("Bounciness", 0.0, 2.0);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiButton* ballClear = gui->addButton("Clear Balls");
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    
    ofxDatGuiSlider* sliderRadius = gui->addSlider("Tombola Size", 150, 300, 100);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiSlider* sliderRotate = gui->addSlider("Tombola Rotate", -4, 4, 0);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    ofxDatGuiSlider* sliderSpin = gui->addSlider("Tombola Spin", -500, 500);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    

    
    gui->addBreak();
    
//    ofxDatGuiButton* getPorts = gui->addButton("Get Midi Out Ports");
//    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    
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
    
    tRadius = 150;
    tLength = 150;
    tWidth = 2;
    
    bBounce = 0.7;
    bDensity = 1.0;
    
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
    
    tombolaScale();
    tombolaRotate();

  //  Not working yet
//    tombolaSpin();

    
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
    
    
    
    for (auto &rect : tRects){
        ofSetColor(200, 0, 80);
        rect->draw();
    };

    

    

};

//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    
    if (e.target->is("Spawn Ball")) {
        // make a shared circle
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(bDensity, bBounce, 0.7);
        circle->setup(box2d.getWorld(), canvasCenter.x, canvasCenter.y, 5);
        circle->shouldRemoveOffScreen(circle);
        
        // assign an instance of the MidiData class to the ball.
        circle->setData(new MidiData());
        auto * md = (MidiData*)circle->getData();
        md->bHit = false;
        
        circles.push_back(circle);
    };
    
    if (e.target->is("Clear Balls")){
        circles.clear();
        
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
   
    
    if (e.target->is("Tombola Size")){
        tRadius = e.value;
        
    } else if (e.target->is("Tombola Rotate")){
        tRotAngle = e.value;
        
        
    } else if (e.target->is("Tombola Spin")){
//        tSpin = e.value;
//        tombolaSpin();
        cout << e.value << endl;
        //        v0r.rotate(e.value, ofVec3f(0, 0, 1));
//        v1r.rotate(e.value, ofVec3f(0, 0, 1));
//        v2r.rotate(e.value, ofVec3f(0, 0, 1));
//        v3r.rotate(e.value, ofVec3f(0, 0, 1));
//        v4r.rotate(e.value, ofVec3f(0, 0, 1));
//        v5r.rotate(e.value, ofVec3f(0, 0, 1));
//
        tRects.at(0)->setPosition(ofVec2f(e.value, e.value));
//        tRects.at(1)->setPosition(v1r - tRects.at(1)->getPosition());
//        tRects.at(2)->setPosition(v2r - tRects.at(2)->getPosition());
//        tRects.at(3)->setPosition(v3r - tRects.at(3)->getPosition());
//        tRects.at(4)->setPosition(v4r - tRects.at(4)->getPosition());
//        tRects.at(5)->setPosition(v5r - tRects.at(5)->getPosition());
//
//        for (auto &tRect : tRects){
//            tRect->setPosition(ofVec2f(e.value, e.value));
//        }
        
    } else if (e.target->is("Bounciness")){
        bBounce = e.value;
        
    } else if (e.target->is("Ball Mass")){
        bDensity = e.value;

    }
    

    
    
    
    
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        // Check what objects are colliding (it seems like a nonsensical
        // check, but without it I was getting pointer access errors...
//        if(e.a->GetType() == b2Shape::e_circle || e.a->GetType() == b2Shape::e_edge) {
            
            cout << "contact start" << endl;
            
            // Dont fully understand what's happening here,
            // but it seems like aData is being set as a pointer to MidiData
            // and - as it now takes the class form - can subsequently use
            // methods from that class as well as the contact listner class
            MidiData * aData = (MidiData*)e.a->GetBody()->GetUserData();
            MidiData * bData = (MidiData*)e.b->GetBody()->GetUserData();


            if(aData) {
                aData->bHit = true;
                bData->update(midi.getName(), 1, 0);
                bData->noteOn();
                cout << "aData collision" << endl;
            };

            if(bData) {
                bData->bHit = true;
                bData->update(midi.getName(), 1, 0);
                bData->noteOn();
                cout << "bData collision" << endl;
            }
            
        
        
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {

        MidiData * aData = (MidiData*)e.a->GetBody()->GetUserData();
        MidiData * bData = (MidiData*)e.b->GetBody()->GetUserData();

        if(aData) {
            aData->bHit = false;
            aData->noteOff();
        }

        if(bData) {
            bData->bHit = false;
            bData->noteOff();
        }
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

    // this feels stupid, not sure if it's the best way.
    // But as each rect needs a differnt initial position and rotation value
    // I'm not sure how else to go about it.
    auto rect0 = std::make_shared<ofxBox2dRect>();
    auto rect1 = std::make_shared<ofxBox2dRect>();
    auto rect2 = std::make_shared<ofxBox2dRect>();
    auto rect3 = std::make_shared<ofxBox2dRect>();
    auto rect4 = std::make_shared<ofxBox2dRect>();
    auto rect5 = std::make_shared<ofxBox2dRect>();
    
    
    rect0->setup(box2d.getWorld(), v0r.x, v0r.y, tLength, tWidth, 60);
    rect1->setup(box2d.getWorld(), v1r.x, v1r.y, tLength, tWidth, 120);
    rect2->setup(box2d.getWorld(), v2r.x, v2r.y, tLength, tWidth, 0);
    rect3->setup(box2d.getWorld(), v3r.x, v3r.y, tLength, tWidth, -120);
    rect4->setup(box2d.getWorld(), v4r.x, v4r.y, tLength, tWidth, -60);
    rect5->setup(box2d.getWorld(), v5r.x, v5r.y, tLength, tWidth, 0);
    

    tRects.push_back(rect0);
    tRects.push_back(rect1);
    tRects.push_back(rect2);
    tRects.push_back(rect3);
    tRects.push_back(rect4);
    tRects.push_back(rect5);

    
}


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
    canvasCenter.set(w / 2, h / 2);
    
    tombolaCenter();

}

//--------------------------------------------------------------
void ofApp::tombolaCenter(){
    
    v0r.set(canvasCenter.x + v0.x - (v1.x / 2), canvasCenter.y + v0.y - (v1.y / 2));
    v1r.set(canvasCenter.x + v1.x - (v2.x / 2), canvasCenter.y + v1.y - (v2.y / 2));
    v2r.set(canvasCenter.x + v2.x - (v3.x / 2), canvasCenter.y + v2.y - (v3.y / 2));
    v3r.set(canvasCenter.x + v3.x - (v4.x / 2), canvasCenter.y + v3.y - (v4.y / 2));
    v4r.set(canvasCenter.x + v4.x - (v5.x / 2), canvasCenter.y + v4.y - (v5.y / 2));
    v5r.set(canvasCenter.x + v5.x - (v0.x / 2), canvasCenter.y + v5.y - (v0.y / 2));
    
    tRects.at(0)->setPosition(v0r);
    tRects.at(1)->setPosition(v1r);
    tRects.at(2)->setPosition(v2r);
    tRects.at(3)->setPosition(v3r);
    tRects.at(4)->setPosition(v4r);
    tRects.at(5)->setPosition(v5r);

}
//--------------------------------------------------------------
void ofApp::tombolaScale(){
    

    // radius set by slder
    v0.set(tRadius * cos(glm::radians(0.0)), tRadius * sin(glm::radians(0.0)), 0);
    v1.set(tRadius * cos(glm::radians(60.0)), tRadius * sin(glm::radians(60.0)), 0);
    v2.set(tRadius * cos(glm::radians(120.0)), tRadius * sin(glm::radians(120.0)), 0);
    v3.set(tRadius * cos(glm::radians(180.0)), tRadius * sin(glm::radians(180.0)), 0);
    v4.set(tRadius * cos(glm::radians(240.0)), tRadius * sin(glm::radians(240.0)), 0);
    v5.set(tRadius * cos(glm::radians(300.0)), tRadius * sin(glm::radians(300.0)), 0);
    
    v0r.set(canvasCenter.x + v0.x - (v1.x / 2), canvasCenter.y + v0.y - (v1.y / 2));
    v1r.set(canvasCenter.x + v1.x - (v2.x / 2), canvasCenter.y + v1.y - (v2.y / 2));
    v2r.set(canvasCenter.x + v2.x - (v3.x / 2), canvasCenter.y + v2.y - (v3.y / 2));
    v3r.set(canvasCenter.x + v3.x - (v4.x / 2), canvasCenter.y + v3.y - (v4.y / 2));
    v4r.set(canvasCenter.x + v4.x - (v5.x / 2), canvasCenter.y + v4.y - (v5.y / 2));
    v5r.set(canvasCenter.x + v5.x - (v0.x / 2), canvasCenter.y + v5.y - (v0.y / 2));
    
    tRects.at(0)->setPosition(v0r);
    tRects.at(1)->setPosition(v1r);
    tRects.at(2)->setPosition(v2r);
    tRects.at(3)->setPosition(v3r);
    tRects.at(4)->setPosition(v4r);
    tRects.at(5)->setPosition(v5r);
    
}

//--------------------------------------------------------------
void ofApp::tombolaRotate(){

    // tRotAngle set by slider
    tRects.at(0)->setRotation(tRotAngle + tRects.at(0)->getRotation());
    tRects.at(1)->setRotation(tRotAngle + tRects.at(1)->getRotation());
    tRects.at(2)->setRotation(tRotAngle + tRects.at(2)->getRotation());
    tRects.at(3)->setRotation(tRotAngle + tRects.at(3)->getRotation());
    tRects.at(4)->setRotation(tRotAngle + tRects.at(4)->getRotation());
    tRects.at(5)->setRotation(tRotAngle + tRects.at(5)->getRotation());
}

//--------------------------------------------------------------
void ofApp::tombolaSpin(){
    // tRotAngle set by slider
    v0r.rotate(tSpin, ofVec3f(0, 1, 0));
    cout << v0r << endl;
    
    tRects.at(0)->setPosition(v0r - tRects.at(0)->getPosition());
    tRects.at(1)->setPosition(v1r - tRects.at(1)->getPosition());
    tRects.at(2)->setPosition(v2r - tRects.at(2)->getPosition());
    tRects.at(3)->setPosition(v3r - tRects.at(3)->getPosition());
    tRects.at(4)->setPosition(v4r - tRects.at(4)->getPosition());
    tRects.at(5)->setPosition(v5r - tRects.at(5)->getPosition());
    
    
//    tRects.at(0)->setPosition(tRects.at(0)->getPosition() += (tRadius * cos(glm::radians(tRects.at(0)->getRotation() + tSpin)), tRadius * sin(glm::radians(tRects.at(0)->getRotation() + tSpin)), 0));
//    tRects.at(1)->setPosition(tRects.at(1)->getPosition() + tRotAngle);
//    tRects.at(2)->setPosition(tRects.at(2)->getPosition() + tRotAngle);
//    tRects.at(3)->setPosition(tRects.at(3)->getPosition() + tRotAngle);
//    tRects.at(4)->setPosition(tRects.at(4)->getPosition() + tRotAngle);
//    tRects.at(5)->setPosition(tRects.at(5)->getPosition() + tRotAngle);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



