//
//  ofTombola.cpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#include "ofTombola.hpp"

ofTombola::ofTombola() {
    
    canvasCenter.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    radius = 200;
    
    // vertex points for hexagon
    v0.set(canvasCenter.x + radius * cos(glm::radians(0.0)), canvasCenter.y + radius * sin(glm::radians(0.0)), 0);
    tombolaVerts.push_back(v0);
    
    v1.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    tombolaVerts.push_back(v1);
    
    v2.set(canvasCenter.x + radius * cos(glm::radians(60.0)), canvasCenter.y + radius * sin(glm::radians(60.0)), 0);
    tombolaVerts.push_back(v2);
    
    v3.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    tombolaVerts.push_back(v3);
    
    v4.set(canvasCenter.x + radius * cos(glm::radians(120.0)), canvasCenter.y + radius * sin(glm::radians(120.0)), 0);
    tombolaVerts.push_back(v4);
    
    v5.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    tombolaVerts.push_back(v5);
    
    v6.set(canvasCenter.x + radius * cos(glm::radians(180.0)), canvasCenter.y + radius * sin(glm::radians(180.0)), 0);
    tombolaVerts.push_back(v6);
    
    v7.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    tombolaVerts.push_back(v7);
    
    v8.set(canvasCenter.x + radius * cos(glm::radians(240.0)), canvasCenter.y + radius * sin(glm::radians(240.0)), 0);
    tombolaVerts.push_back(v8);
    
    v9.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    tombolaVerts.push_back(v9);
    
    v10.set(canvasCenter.x + radius * cos(glm::radians(300.0)), canvasCenter.y + radius * sin(glm::radians(300.0)), 0);
    tombolaVerts.push_back(v10);
    
    v11.set(canvasCenter.x + radius * cos(glm::radians(360.0)), canvasCenter.y + radius * sin(glm::radians(360.0)), 0);
    tombolaVerts.push_back(v11);
    
    
    

}

ofTombola::~ofTombola(){
    
}


void ofTombola::update(int radiusMod) {
    v0 += radiusMod;
    v1 += radiusMod;
}



void ofTombola::draw() {
    
//    ofDrawEllipse(712, 384, 20, 20); // just a marker for the first point for visual debugging
    tombolaLine.lineTo(v0);
    tombolaLine.lineTo(v1);

    tombolaLine.lineTo(v2);
    tombolaLine.lineTo(v3);

    tombolaLine.lineTo(v4);
    tombolaLine.lineTo(v5);

    tombolaLine.lineTo(v6);
    tombolaLine.lineTo(v7);

    tombolaLine.lineTo(v8);
    tombolaLine.lineTo(v9);

    tombolaLine.lineTo(v10);
    tombolaLine.lineTo(v11);
    
    auto edges = std::make_shared<ofxBox2dEdge>();
    edges->addVertexes(tombolaLine);
    edges->create(box2d.getWorld());
    edges->draw();
  //  tombolaLine.draw();


}
