//
//  tombola.hpp
//  CC2-tombola-xcode
//
//  Created by Tillman on 12.08.22.
//

#ifndef ofTombola_hpp
#define ofTombola_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

#endif /* ofTombola_hpp */

class ofTombola {
    
public:
    ofTombola();
    ~ofTombola();
    
    void update(int radiusMod);
    void draw();
    
    ofPoint pointA;
    ofPoint pointB;
    
    vector <ofVec2f> tombolaVerts;
    vector <shared_ptr<ofxBox2dEdge>> edges;
    

  
private:
    ofColor color{};
    float rotation{};
    float spinSpeed{};
    float radius{};
    
    //vector <ofPolyline> tombolaLines;
    
    ofPolyline tombolaLine;
    
    ofVec3f v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
    ofVec3f v0mod, m1mod, v2mod, v3mod;
    
    // tomobola measurement utility
    ofVec2f canvasCenter;
    


    

    
};
