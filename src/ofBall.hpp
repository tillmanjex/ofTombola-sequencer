//
//  ofBall.hpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#pragma once
#ifndef ofBall_hpp
#define ofBall_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

#endif /* ofBall_hpp */

class ofBall {
    
public:
    ofBall();
    ~ofBall();
    
    // define member functions - ie the definition of the class and how to use it
    void update();
    void draw();
    void setMusicalParams(); // receive and storing midi data?
    void playNote(); // basically play note on collision - take data from setMusicalParams();
    void musicalScale();
//    void collision(ofVec3f vertexA, ofVec3f vertexB);
    
//    int bouncieness{};
//    int radius{10};
    int noteValue{};
//    float distance{};
//    ofVec3f intersection;
//    ofVec2f lineSegA;
    
    // Box2d
    ofxBox2d box2d;
    //ofxBox2dCircle ball;
    
    
    // Forces
//    ofVec3f location;
//    ofVec3f velocity;
//    ofVec3f acceleration;
//    ofVec3f speed;
//    float mass{10};
    
    

    
    
private:
    
    ofColor color{};
    ofVec2f canvasCenter{};
    float topspeed{9.8};
    

    
    
    
    

    
};
