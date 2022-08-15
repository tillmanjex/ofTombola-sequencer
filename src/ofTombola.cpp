//
//  ofTombola.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofTombola.hpp"
#include "ofApp.h"

ofTombola::ofTombola() {
    
    length = 5;
    width = 1;
    radius = 10;
    rotation = 0;
    spinSpeed = 0;
    color.set(255);
}

void ofTombola::update() {
    
}


void ofTombola::draw() {
    pt.set(100, 200);
    tombolaLine.addVertex(pt);
    tombolaLine.draw();
}
