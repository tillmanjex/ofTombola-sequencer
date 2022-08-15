//
//  ofTombola.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofTombola.hpp"

ofTombola::ofTombola() {
    
    radius = 10;
    rotation = 0;
    spinSpeed = 0;
    color.set(255);
    v0.set(100, 150, 0);
    v1.set(200, 200, 0);
}

ofTombola::~ofTombola(){
    
}

void ofTombola::update() {
    
}


void ofTombola::draw() {
    tombolaLine.lineTo(v0);
    tombolaLine.lineTo(v1);
    tombolaLine.draw();


}
