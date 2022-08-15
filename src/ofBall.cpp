//
//  ofBall.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofBall.hpp"


ofBall::ofBall() {

    int radius {10};
    canvasCenter.set(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // Forces
    location.set(canvasCenter.x, canvasCenter.y);
    velocity.set(ofRandom(1.0), 2);
    
}

ofBall::~ofBall() {
    
}

void ofBall::update() {
    location += velocity;
}

void ofBall::draw() {
    
    ofDrawEllipse(location.x, location.y, radius, radius);
}

void ofBall::setMusicalParams() {
    
}

void ofBall::playNote() {
    
}

void ofBall::musicalScale() {
    
}
