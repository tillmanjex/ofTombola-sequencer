//
//  ofTombola.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofTombola.hpp"

ofTombola::ofTombola() {
    
    
    rotation = 0;
    spinSpeed = 0;
    color.set(255, 0, 0); // not working yet
    centerX = ofGetWindowWidth() / 2;
    centerY = ofGetWindowHeight() / 2;
    
    // vertex points for hexagon
    radius = 200;
    
    v0.set(centerX + radius * cos(glm::radians(0.0)), centerY + radius * sin(glm::radians(0.0)), 0);
    v1.set(centerX + radius * cos(glm::radians(60.0)), centerY + radius * sin(glm::radians(60.0)), 0);
    v2.set(centerX + radius * cos(glm::radians(60.0)), centerY + radius * sin(glm::radians(60.0)), 0);
    v3.set(centerX + radius * cos(glm::radians(120.0)), centerY + radius * sin(glm::radians(120.0)), 0);
    v4.set(centerX + radius * cos(glm::radians(120.0)), centerY + radius * sin(glm::radians(120.0)), 0);
    v5.set(centerX + radius * cos(glm::radians(180.0)), centerY + radius * sin(glm::radians(180.0)), 0);
    v6.set(centerX + radius * cos(glm::radians(180.0)), centerY + radius * sin(glm::radians(180.0)), 0);
    v7.set(centerX + radius * cos(glm::radians(240.0)), centerY + radius * sin(glm::radians(240.0)), 0);
    v8.set(centerX + radius * cos(glm::radians(240.0)), centerY + radius * sin(glm::radians(240.0)), 0);
    v9.set(centerX + radius * cos(glm::radians(300.0)), centerY + radius * sin(glm::radians(300.0)), 0);
    v10.set(centerX + radius * cos(glm::radians(300.0)), centerY + radius * sin(glm::radians(300.0)), 0);
    v11.set(centerX + radius * cos(glm::radians(360.0)), centerY + radius * sin(glm::radians(360.0)), 0);
    
    //ofLog() << v0 ;
}

ofTombola::~ofTombola(){
    
}


void ofTombola::update(int radiusMod) {
    v0 += radiusMod;
    v1 += radiusMod;
}




void ofTombola::draw() {
    // The lines need to be drawn as singular lines, hence the draw/clear sequencing
    ofDrawEllipse(712, 384, 20, 20); // just a marker for the first point for visual debugging
    tombolaLine.lineTo(v0);
    tombolaLine.lineTo(v1);
    tombolaLine.draw();
    tombolaLine.clear();
    
    tombolaLine.lineTo(v2);
    tombolaLine.lineTo(v3);
    tombolaLine.draw();
    tombolaLine.clear();
    
    tombolaLine.lineTo(v4);
    tombolaLine.lineTo(v5);
    tombolaLine.draw();
    tombolaLine.clear();
    
    tombolaLine.lineTo(v6);
    tombolaLine.lineTo(v7);
    tombolaLine.draw();
    tombolaLine.clear();
    
    tombolaLine.lineTo(v8);
    tombolaLine.lineTo(v9);
    tombolaLine.draw();
    tombolaLine.clear();
    
    tombolaLine.lineTo(v10);
    tombolaLine.lineTo(v11);
    tombolaLine.draw();
    tombolaLine.clear();


}
