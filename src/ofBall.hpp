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
    
    
private:
    int ballSize{};
    int bouncieness{};
    
    int noteValue{};
    ofColor color{};
    
    //dynamics
    int mass{}; // useful for changing mass before ball generation to make more varied collission rhythms
    float xSpeed{};
    float ySpeed{};
    float acceleration{};
    float gravity{};
    
    

};
