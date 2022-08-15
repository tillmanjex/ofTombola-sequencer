//
//  ofTombola.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofTombola.hpp"

ofTombola::ofTombola() {
    
    
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
    // vertex points for hexagon
    radius = 200;
    
    v0.set(canvasCenter.x + radius * cos(glm::radians(0.0)), canvasCenter.y + radius * sin(glm::radians(0.0)), 0);
    v1.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    v2.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    v3.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    v4.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    v5.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    v6.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    v7.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    v8.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    v9.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    v10.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    v11.set(canvasCenter.x + radius * cos(glm::radians(360.0)), canvasCenter.y + radius * sin(glm::radians(360.0)), 0);
    
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
