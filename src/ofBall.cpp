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
    location.set(canvasCenter.x, canvasCenter.y, 0.0);
    acceleration.set(00., 0.05, 0.0);
    velocity.set(ofRandom(-1.0, 1.0), ofRandom(-1.0, -2.0), 0.0);
    
    
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

void ofBall::collision(ofVec3f vertexA, ofVec3f vertexB) {
    
//    ofLineSegmentIntersection(lineSegA.set(vertexA.x, vertexA.y), ofVec2f(vertexB.x, vertexB.y), ofVec2f(location.x, location.y), ofVec2f(location.x, location.y), intersection);
//    cout << intersection << endl;
    
//    distance = vertexA.distance(location) + vertexB.distance(location);
//    cout << distance << endl;
//    if (distance == vertexA.distance(vertexB)){
//        cout << "ball collided" << endl;
//    };
}


void ofBall::setMusicalParams() {
    
}

void ofBall::playNote() {
    // collision with tombola
    
}

void ofBall::musicalScale() {
    
}
