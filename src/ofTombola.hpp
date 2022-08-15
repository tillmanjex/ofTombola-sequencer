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
    
    void update();
    void draw();
    
    ofPoint pointA;
    ofPoint pointB;
  
private:
    ofColor color{};
    float rotation{};
    float spinSpeed{};
    float radius{};
    ofPolyline tombolaLine;
    ofVec3f v0, v1;
    

    
};
