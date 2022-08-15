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

#endif /* ofTombola_hpp */

class ofTombola {
    
public:
    ofTombola();
    ~ofTombola();
    
    void update(int radiusMod);
    void draw();
    
    ofPoint pointA;
    ofPoint pointB;
  
private:
    ofColor color{};
    float rotation{};
    float spinSpeed{};
    float radius{};
    ofPolyline tombolaLine;
    ofVec3f v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
    ofVec3f v0mod, m1mod, v2mod, v3mod;
    
    // tomobola measurement utility
    int centerX;
    int centerY;


    

    
};
