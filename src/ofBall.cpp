//
//  ofBall.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofBall.hpp"


ofBall::ofBall() {

    canvasCenter.set(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // Forces
    location.set(canvasCenter.x, canvasCenter.y);
    acceleration.set(00., 0.05);
    velocity.set(ofRandom(-1.0, 1.0), (-1.0, -2.0));
    
    
}

ofBall::~ofBall() {
    
}

void ofBall::update() {
    velocity += acceleration;
    velocity.limit(topspeed);
    location += velocity;
    
    
}

void ofBall::draw() {
    
    ofDrawEllipse(location.x, location.y, radius, radius);

}

void ofBall::setMusicalParams() {
    
}

void ofBall::playNote() {
    // collision with tombola
    
}

void ofBall::musicalScale() {
    
}
